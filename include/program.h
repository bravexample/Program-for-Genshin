#ifndef PROGRAM_H
#define PROGRAM_H

#include "stdlib.h"
#include "SDL/SDL.h"
#include "windows.h"

static const int windowWidth = 500;
static const int windowHeight = 200;
static const char *pictureName[] = {
	"picture/idle.bmp",
	"picture/fast_shot.bmp",
	"picture/skip.bmp"
};
static const int pictureAmount = sizeof(pictureName) / sizeof(char *);

typedef struct PROGRAM {
	SDL_Window *window;
	SDL_Surface *surface;
	SDL_Surface **pictureArray;
} PROGRAM;

static PROGRAM program;

static inline void PROGRAM_clean() {
	for (int i = 0; i < pictureAmount; i++) {
		if (program.pictureArray[i]) 
			SDL_FreeSurface(program.pictureArray[i]);
	}

	free(program.pictureArray);

	SDL_DestroyWindow(program.window);		
	
	SDL_Quit();
}

static inline void PROGRAM_setup() {
	if (SDL_Init(SDL_INIT_VIDEO)) {
		MessageBox(0, "SDL failed initializing.", 0, MB_OK);
		exit(-1);
	}

	program.window = SDL_CreateWindow("Program for Genshin", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_VULKAN);
	if (!program.window) {
		MessageBoxA(0, "SDL failed creating window.", 0, MB_OK);
		SDL_Quit();
		exit(-1);
	}

	program.surface = SDL_GetWindowSurface(program.window);

	program.pictureArray = (SDL_Surface **)calloc(pictureAmount, sizeof(SDL_Surface *));

	for (int i = 0; i < pictureAmount; i++) {
		program.pictureArray[i] = SDL_LoadBMP(pictureName[i]);
		if (!program.pictureArray[i]) {
			MessageBoxA(0, "SDL failed loading image.", 0, MB_OK);
			PROGRAM_clean();
			exit(-1);
		}
	}
}

static inline void PROGRAM_render(const int index) {
	SDL_BlitSurface(program.pictureArray[index], 0, program.surface, 0);
	SDL_UpdateWindowSurface(program.window);
}

static INPUT inputs[6] = {
	{
		.type = INPUT_MOUSE,
		.mi.dwFlags = MOUSEEVENTF_LEFTDOWN
	},{
		.type = INPUT_MOUSE,
		.mi.dwFlags = MOUSEEVENTF_LEFTUP
	},{
		.type = INPUT_MOUSE,
		.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN
	},{
		.type = INPUT_MOUSE,
		.mi.dwFlags = MOUSEEVENTF_RIGHTUP
	},{
		.type = INPUT_KEYBOARD,
		.ki.dwFlags = 0
	},{
		.type = INPUT_KEYBOARD,
		.ki.dwFlags = KEYEVENTF_KEYUP
	}
};

static const int INPUTsize = sizeof(INPUT);

static inline void mouse_click(const char mouseKey) {
	if (mouseKey == 'l') 
		SendInput(2, inputs, INPUTsize);
	else
		SendInput(2, inputs + 2, INPUTsize);
}

static inline void key_press(const char key) {
	inputs[4].ki.wVk = key;
	inputs[5].ki.wVk = key;
	SendInput(2, inputs + 4, INPUTsize);
}

#endif