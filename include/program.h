#ifndef PROGRAM_H
#define PROGRAM_H

#include <stdlib.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "windows.h"

typedef struct PROGRAM {
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Surface *surface;
	SDL_Texture **textureArray;
	long long textureArrayEnd;
} PROGRAM;

PROGRAM *PROGRAM_create(const int, const int);

void PROGRAM_alloc_textures(PROGRAM *, const int);

void PROGRAM_load_image(PROGRAM *, const char *, const int);

void PROGRAM_delete(PROGRAM *);

void mouse_click(const char);

void key_press(const char);

#endif