#include "program.h"

PROGRAM *PROGRAM_create(const int windowWidth, const int windowHeight) {
	PROGRAM *newPROGRAM = (PROGRAM *)calloc(1, sizeof(PROGRAM));

	newPROGRAM->window = SDL_CreateWindow("Program for Genshin", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_VULKAN);
	if (!newPROGRAM->window) {
		MessageBox(0, "SDL failed creating window.", 0, MB_OK);
		free(newPROGRAM);
		exit(-1);
	}

	newPROGRAM->surface = SDL_GetWindowSurface(newPROGRAM->window);

	return newPROGRAM;
}

void PROGRAM_load_image(PROGRAM *program, const char **nameArray, const int size) {
	program->pictureArray = (SDL_Surface **)calloc(size, sizeof(SDL_Surface *));
	program->pictureArrayEnd = size;

	for (int i = 0; i < size; i++) {
		program->pictureArray[i] = SDL_LoadBMP(nameArray[i]);
		if (!program->pictureArray[i]) {
			MessageBox(0, "SDL failed loading image.", 0, MB_OK);
			PROGRAM_delete(program);
			exit(-1);
		}
	}
}

void PROGRAM_render(const PROGRAM *program, const int index) {
	SDL_BlitSurface(program->pictureArray[index], 0, program->surface, 0);
	SDL_UpdateWindowSurface(program->window);
}

void PROGRAM_delete(PROGRAM *program) {
	if (program->pictureArray) {
		for (long long i = 0; i < program->pictureArrayEnd; i++) {
			if (program->pictureArray[i]) 
				SDL_FreeSurface(program->pictureArray[i]);
		}

		free(program->pictureArray);
	}

	if (program->window) 
		SDL_DestroyWindow(program->window);

	free(program);
}

INPUT inputs[6] = {
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

void mouse_click(const char mouseKey) {
	if (mouseKey == 'l') 
		SendInput(2, inputs, sizeof(INPUT));
	else
		SendInput(2, inputs + 2, sizeof(INPUT));
}

void key_press(const char key) {
	inputs[4].ki.wVk = key;
	inputs[5].ki.wVk = key;
	SendInput(2, inputs + 4, sizeof(INPUT));
}