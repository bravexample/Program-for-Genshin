#include "program.h"

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	if (SDL_Init(SDL_INIT_EVERYTHING)) {
		MessageBox(0, "SDL failed initializing.", 0, MB_OK);
		return -1;
	}

	int imageFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imageFlags) & imageFlags)) {
		MessageBox(0, "SDL_image failed initializing.", 0, MB_OK);
		return -1;
	}

	const int windowWidth = 500;
	const int windowHeight = 200;
	const int pictureNumber = 3;
	const char *pictureName[3] = {
		"picture/idle.png",
		"picture/fast_shot.png",
		"picture/skip.png"
	};

	PROGRAM *program = PROGRAM_create(windowWidth, windowHeight);

	PROGRAM_alloc_textures(program, pictureNumber);
	
	for (int i = 0; i < pictureNumber; i++) 
		PROGRAM_load_image(program, pictureName[i], i);

	SDL_Event event;
	int state = 0, tempState = -1;

	do {
		Sleep(50);
	
		if (GetKeyState('V')) 
			state = 1;
		else if (GetKeyState('N')) 
			state = 2;
		else 
			state = 0;

		if (state != tempState) {
			PROGRAM_render_texture(program, state);
			tempState = state;
		}
	
		if (state == 1) {
			mouse_click('l');
			Sleep(400);
			key_press('R');
			Sleep(50);
			key_press('R');
		} else if (state == 2) 
			mouse_click('l');
	
		SDL_PollEvent(&event);
	} while (event.type != SDL_QUIT);

	PROGRAM_delete(program);
	IMG_Quit();
	SDL_Quit();
	return 0;
}
