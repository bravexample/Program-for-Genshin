#include "program.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance,
                   _In_opt_ HINSTANCE hPrevInstance,
                   _In_ LPSTR lpCmdLine,
                   _In_ int nShowCmd)
{
	(void )hPrevInstance; (void )lpCmdLine;

	Setup(hInstance, nShowCmd);

	threadState = 1;
	HANDLE thread = CreateThread(NULL, 0, ThreadProc, NULL, 0, NULL);

	MSG msg = {0};
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	WaitForSingleObject(thread, INFINITE);

	return (int )msg.wParam;
}
