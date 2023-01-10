#include "SDL.h"
#include "SDL_image.h"
#include "windows.h"
#include "winuser.h"

int WinMain() {
	if (SDL_Init(SDL_INIT_EVERYTHING)) return -1;

	const int windowWidth = 500;
	const int windowHeight = 200;

	SDL_Window* window = SDL_CreateWindow("SDL Yoimiya Macro", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_VULKAN);
	if (!window) return -1;

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer) return -1;

	int imageFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imageFlags) & imageFlags)) return -1;

	SDL_Surface* surface = IMG_Load("idle.png");
	if (!surface) return -1;

	SDL_Texture* texture[3] = { 0 };
	texture[0] = SDL_CreateTextureFromSurface(renderer, surface);
	if (!texture[0]) return -1;

	SDL_FreeSurface(surface);
	surface = IMG_Load("fast_shot.png");
	texture[1] = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_FreeSurface(surface);
	surface = IMG_Load("skip.png");
	texture[2] = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_Event event;
	int state = 0;
	INPUT inputs[4];
	inputs[0].type = INPUT_MOUSE;
	inputs[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	inputs[1].type = INPUT_MOUSE;
	inputs[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;
	inputs[2].type = INPUT_KEYBOARD;
	inputs[2].ki.wVk = 'R';
	inputs[2].ki.dwFlags = 0;
	inputs[3].type = INPUT_KEYBOARD;
	inputs[3].ki.wVk = 'R';
	inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;

	do {
		SDL_RenderCopy(renderer, texture[state], NULL, NULL);
		SDL_RenderPresent(renderer);

		if (state == 1) {
			SendInput(2, inputs, sizeof(INPUT));
			Sleep(400);
			SendInput(2, inputs + 2, sizeof(INPUT));
			Sleep(50);
			SendInput(2, inputs + 2, sizeof(INPUT));
			Sleep(50);
		}
		else if (state == 2) {
			SendInput(2, inputs, sizeof(INPUT));
			Sleep(50);
		}

		if (GetKeyState('V')) state = 1;
		else if (GetKeyState('N')) state = 2;
		else state = 0;

		SDL_PollEvent(&event);
	} while (event.type != SDL_QUIT);

	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
	IMG_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}