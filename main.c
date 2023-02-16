#include "program.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	PROGRAM_setup();

	SDL_Event event;
	int state = 0, tempState = -1;

	do {
		Sleep(25);
	
		if (GetKeyState('V')) 
			state = 1;
		else if (GetKeyState('N')) 
			state = 2;
		else 
			state = 0;

		if (state != tempState) {
			PROGRAM_render(state);
			tempState = state;
		}
	
		if (state == 1) {
			mouse_click('l');
			Sleep(400);
			key_press('R');
			Sleep(40);
			key_press('R');
		}
		else if (state == 2) 
			mouse_click('l');
	
		SDL_PollEvent(&event);
	} while (event.type != SDL_QUIT);

	PROGRAM_clean();
	return 0;
}
