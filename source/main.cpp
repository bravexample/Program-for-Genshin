#include "program.hpp"

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
	vector<string> pictureName = {
		"picture/idle.png",
		"picture/fast_shot.png",
		"picture/skip.png"
	};

	PROGRAM program(windowWidth, windowHeight);

	program.alloc_textures(pictureName.size());
	
	for (int i = 0; i < (int )pictureName.size(); i++) 
		program.load_image(pictureName[i], i);

	SDL_Event event;
	VIRTUALINPUT input;
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
			program.render_texture(state);
			tempState = state;
		}
	
		if (state == 1) {
			input.mouse('l');
			Sleep(400);
			input.keyboard('R');
			Sleep(35);
			input.keyboard('R');
		} else if (state == 2) 
			input.mouse('l');
	
		SDL_PollEvent(&event);
	} while (event.type != SDL_QUIT);

	program.clean();
	IMG_Quit();
	SDL_Quit();
	return 0;
}
