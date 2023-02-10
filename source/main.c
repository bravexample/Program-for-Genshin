#include "program.h"

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	if (SDL_Init(SDL_INIT_VIDEO)) {
		MessageBox(0, "SDL failed initializing.", 0, MB_OK);
		return -1;
	}

	const int windowWidth = 500;
	const int windowHeight = 200;
	const char *pictureName[] = {
		"picture/idle.bmp",
		"picture/fast_shot.bmp",
		"picture/skip.bmp"
	};

	PROGRAM *program = PROGRAM_create(windowWidth, windowHeight);

	PROGRAM_load_image(program, pictureName, sizeof(pictureName) / sizeof(const char *));

	SDL_Event event;
	int state = 0, tempState = -1;

	do {
		Sleep(35);
	
		if (GetKeyState('V')) 
			state = 1;
		else if (GetKeyState('N')) 
			state = 2;
		else 
			state = 0;

		if (state != tempState) {
			PROGRAM_render(program, state);
			tempState = state;
		}
	
		if (state == 1) {
			mouse_click('l');
			Sleep(400);
			key_press('R');
			Sleep(35);
			key_press('R');
		}
		else if (state == 2) 
			mouse_click('l');
	
		SDL_PollEvent(&event);
	} while (event.type != SDL_QUIT);

	PROGRAM_delete(program);
	SDL_Quit();
	return 0;
}