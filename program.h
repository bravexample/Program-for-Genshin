#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>

#define WINDOWWIDTH         1000
#define WINDOWHEIGHT        100
#define WINDOWSTYLE         WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX
#define PROGRAM_NAME        "Program for Genshin"
#define STRINGFORMAT        DT_CENTER | DT_SINGLELINE | DT_VCENTER
#define FONTPITCHFAMILY     DEFAULT_PITCH | FF_DONTCARE
#define WHITE               RGB(255, 255, 255)
#define BLACK               RGB(0, 0, 0)
#define MOUSELEFTDOWN       SendInput(1, virtualInputs, inputSize)
#define MOUSELEFTUP         SendInput(1, virtualInputs + 1, inputSize)
#define MOUSERIGHTDOWN      SendInput(1, virtualInputs + 2, inputSize)
#define MOUSERIGHTUP        SendInput(1, virtualInputs + 3, inputSize)
#define MOUSETURNAROUND     SendInput(1, virtualInputs + 4, inputSize)

static HWND         window          = 0;
static HDC          windowDC        = 0;
static RECT         windowRECT      = {0};
static HFONT        windowFONT      = {0};
static WNDCLASSA    windowClass     = {0};
static HBRUSH       WhiteBRUSH      = {0};
static HBRUSH       BlackBRUSH      = {0};
static const char*  stateNames[]    =
    {
        "IDLE",
        "SKIP",
        "YOIMIYA",
        "HUTAO",
        "NEUVILLETTE",
    };
static const int    inputSize       = sizeof(INPUT);
static INPUT        virtualInputs[] =
    {
        {.type = INPUT_MOUSE, .mi.dwFlags = MOUSEEVENTF_LEFTDOWN},
        {.type = INPUT_MOUSE, .mi.dwFlags = MOUSEEVENTF_LEFTUP},
        {.type = INPUT_MOUSE, .mi.dwFlags = MOUSEEVENTF_RIGHTDOWN},
        {.type = INPUT_MOUSE, .mi.dwFlags = MOUSEEVENTF_RIGHTUP},
        {.type = INPUT_MOUSE, .mi.dx = 1000, .mi.dwFlags = MOUSEEVENTF_MOVE},
        {.type = INPUT_KEYBOARD, .ki.dwFlags = 0},
        {.type = INPUT_KEYBOARD, .ki.dwFlags = KEYEVENTF_KEYUP}
    };
static int          threadState     = 0;

static inline LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        threadState = 0;
        PostQuitMessage(0);
        return 0;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

static inline void Setup(const HINSTANCE hInstance, const int nCmdShow)
{
    windowClass.lpfnWndProc   = WindowProc;
    windowClass.hInstance     = hInstance;
    windowClass.lpszClassName = PROGRAM_NAME;
    RegisterClassA(&windowClass);

    window = CreateWindowExA(0, PROGRAM_NAME, PROGRAM_NAME, WINDOWSTYLE,
                            CW_USEDEFAULT, CW_USEDEFAULT, WINDOWWIDTH, WINDOWHEIGHT,
                            NULL, NULL, hInstance, NULL);
    if (!window)
    {
        MessageBoxA(NULL, "Error creating window", NULL, MB_OK);
        exit(-1);
    }

    GetClientRect(window, &windowRECT);

    windowFONT = CreateFontA(WINDOWHEIGHT, 0, 0, 0, FW_NORMAL,
                            FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                            DEFAULT_QUALITY, FONTPITCHFAMILY, "Consolas");

    windowDC = GetDC(window);
    HFONT oldFont = (HFONT )SelectObject(windowDC, windowFONT);
    DeleteObject(oldFont);

    WhiteBRUSH = CreateSolidBrush(WHITE);
    BlackBRUSH = CreateSolidBrush(BLACK);

    ShowWindow(window, nCmdShow);
}

static inline void State_Update(int state)
{
    if (state)
    {
        FillRect(windowDC, &windowRECT, BlackBRUSH);
        SetBkColor(windowDC, BLACK);
        SetTextColor(windowDC, WHITE);
    }
    else
    {
        FillRect(windowDC, &windowRECT, WhiteBRUSH);
        SetBkColor(windowDC, WHITE);
        SetTextColor(windowDC, BLACK);
    }

    DrawTextA(windowDC, stateNames[state], -1, &windowRECT, STRINGFORMAT);
    UpdateWindow(window);
}

static inline void key_press(const char key)
{
    virtualInputs[5].ki.wVk = key;
    virtualInputs[6].ki.wVk = key;
    SendInput(2, virtualInputs + 4, inputSize);
}

static inline DWORD WINAPI ThreadProc(LPVOID lpParameter)
{
    (void )lpParameter;
    int state = 0, stateNow = -1;

    while (threadState)
    {
        if (GetKeyState('N'))       state = 1;
        else if (GetKeyState('V'))  state = 2;
        else if (GetKeyState('H'))  state = 3;
        else if (GetKeyState('Z'))  state = 4;
        else                        state = 0;

        if (state != stateNow)
        {
            State_Update(state);
            stateNow = state;
        }

        switch (state)
        {
        case 1:
            MOUSELEFTDOWN;
            MOUSELEFTUP;
            break;
        case 2:
            MOUSELEFTDOWN;
            MOUSELEFTUP;
            Sleep(400);
            key_press('R');
            Sleep(40);
            key_press('R');
            break;
        case 3:
            MOUSELEFTDOWN;
            Sleep(800);
            MOUSELEFTUP;
            key_press(' ');
            Sleep(560);
            break;
        case 4:
            MOUSETURNAROUND;
        }

        Sleep(40);
    }

    return 0;
}
