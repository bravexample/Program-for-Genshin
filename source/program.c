#include "program.h"

PROGRAM *PROGRAM_create(const int windowWidth, const int windowHeight) {
	PROGRAM *newPROGRAM = (PROGRAM *)calloc(1, sizeof(PROGRAM));

	newPROGRAM->window = SDL_CreateWindow("Program for Genshin", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_VULKAN);
	if (!newPROGRAM->window) {
		MessageBox(0, "SDL failed creating window.", 0, MB_OK);
		free(newPROGRAM);
		exit(-1);
	}

	newPROGRAM->renderer = SDL_CreateRenderer(newPROGRAM->window, -1, 0);
	if (!newPROGRAM->renderer) {
		MessageBox(0, "SDL failed setting renderer.", 0, MB_OK);
		PROGRAM_delete(newPROGRAM);
		exit(-1);
	}

	return newPROGRAM;
}

void PROGRAM_alloc_textures(PROGRAM * program, const int size) {
	if (program->textureArray) {
		MessageBox(0, "Don't try to allocate textures twice.", 0, MB_OK);
		return;
	}

	program->textureArray = (SDL_Texture **)calloc(size, sizeof(SDL_Texture *));
	program->textureArrayEnd = size - 1;
}

void PROGRAM_load_image(PROGRAM *program, const char *filename, const int index) {
    if (index < 0 || index > program->textureArrayEnd) {
        MessageBox(0, "Texture index out of range.", 0, MB_OK);
		PROGRAM_delete(program);
		exit(-1);
    }

	if (!program->surface) SDL_FreeSurface(program->surface);

	program->surface = IMG_Load(filename);
    if (!program->surface) {
		MessageBox(0, "Failed loading image.", 0, MB_OK);
		PROGRAM_delete(program);
		exit(-1);
	}

	if (program->textureArray[index]) SDL_DestroyTexture(program->textureArray[index]);

    program->textureArray[index] = SDL_CreateTextureFromSurface(program->renderer, program->surface);
	if (!program->textureArray[index]) {
		MessageBox(0, "Failed creating texture.", 0, MB_OK);
		PROGRAM_delete(program);
		exit(-1);
	}
}

void PROGRAM_render_texture(PROGRAM *program, const int index) {
	SDL_RenderCopy(program->renderer, program->textureArray[index], 0, 0);
	SDL_RenderPresent(program->renderer);
}

void PROGRAM_delete(PROGRAM *program) {
    if (!program) return;

    if (program->textureArray) {
        for (long long i = 0; i < program->textureArrayEnd; i++) {
            if (program->textureArray[i]) SDL_DestroyTexture(program->textureArray[i]);
        }
    }

	if (!program->surface) SDL_FreeSurface(program->surface);

    if (program->renderer) SDL_DestroyRenderer(program->renderer);

    if (program->window) SDL_DestroyWindow(program->window);

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
	if (mouseKey == 'l') SendInput(2, inputs, sizeof(INPUT));
	else if (mouseKey == 'r') SendInput(2, inputs + 2, sizeof(INPUT));
	else MessageBox(0, "WTF is the mouse?", 0, MB_OK);
}

void key_press(const char key) {
	if (key < 'A' || key > 'Z') MessageBox(0, "WTF you want to press?", 0, MB_OK);
	else {
		inputs[4].ki.wVk = key;
		inputs[5].ki.wVk = key;
		SendInput(2, inputs + 4, sizeof(INPUT));
	}
}
