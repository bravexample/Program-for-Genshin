#ifndef PROGRAM_H
#define PROGRAM_H

#include <stdlib.h>
#include "SDL/SDL.h"
#include "windows.h"

typedef struct PROGRAM {
	SDL_Window *window;
	SDL_Surface *surface;
	SDL_Surface **pictureArray;
	long long pictureArrayEnd;
} PROGRAM;

PROGRAM *PROGRAM_create(const int, const int);

void PROGRAM_load_image(PROGRAM *, const char **, const int);

void PROGRAM_render(const PROGRAM *, const int);

void PROGRAM_delete(PROGRAM *);

void mouse_click(const char);

void key_press(const char);

#endif