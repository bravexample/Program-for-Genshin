#include "program.hpp"

PROGRAM::PROGRAM(const int windowWidth, const int windowHeight) {
	_window = SDL_CreateWindow("Program for Genshin", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_VULKAN);
	if (!_window) {
		MessageBox(0, "SDL failed creating window.", 0, MB_OK);
		exit(-1);
	}

	_renderer = SDL_CreateRenderer(_window, -1, 0);
	if (!_renderer) {
		MessageBox(0, "SDL failed setting renderer.", 0, MB_OK);
		clean();
		exit(-1);
	}
}

PROGRAM::~PROGRAM() {}

void PROGRAM::alloc_textures(const int size) {
	if (!_textureArray.empty()) {
		for_each(_textureArray.begin(),
				 _textureArray.end(),
				 [] (auto &element) {
					if (element)
						SDL_DestroyTexture(element);
				 });
		
		_textureArray.clear();
	}

	_textureArray.resize(size);
}

void PROGRAM::load_image(const string &filename, const int index) {
	if (index < 0 || index > (int )_textureArray.size()) {
		MessageBox(0, "Texture index out of range.", 0, MB_OK);
		clean();
		exit(-1);
	}

	if (_surface) 
		SDL_FreeSurface(_surface);

	_surface = IMG_Load(filename.c_str());
	if (!_surface) {
		MessageBox(0, "Failed loading image.", 0, MB_OK);
		clean();
		exit(-1);
	}

	if (_textureArray[index]) 
		SDL_DestroyTexture(_textureArray[index]);

	_textureArray[index] = SDL_CreateTextureFromSurface(_renderer, _surface);
	if (!_textureArray[index]) {
		MessageBox(0, "Failed creating texture.", 0, MB_OK);
		clean();
		exit(-1);
	}
}

void PROGRAM::render_texture(const int index) const {
	if (!_textureArray[index]) {
		MessageBox(0, "Try to render null texture.", 0, MB_OK);
		return;
	}

	SDL_RenderCopy(_renderer, _textureArray[index], 0, 0);
	SDL_RenderPresent(_renderer);
}

void PROGRAM::clean() {
	if (!_textureArray.empty()) {
		for_each(_textureArray.begin(),
				 _textureArray.end(),
				 [] (auto &element) {
					if (element)
						SDL_DestroyTexture(element);
				 });
		
		_textureArray.clear();
	}

	if (_surface) {
		SDL_FreeSurface(_surface);
		_surface = 0;
	}

	if (_renderer) {
		SDL_DestroyRenderer(_renderer);
		_renderer = 0;
	}

	if (_window) {
		SDL_DestroyWindow(_window);
		_window = 0;
	}
}

VIRTUALINPUT::VIRTUALINPUT() {
	_leftMouse[0].type = INPUT_MOUSE;
	_leftMouse[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	_leftMouse[1].type = INPUT_MOUSE;
	_leftMouse[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;

	_rightMouse[0].type = INPUT_MOUSE;
	_rightMouse[0].mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
	_rightMouse[1].type = INPUT_MOUSE;
	_rightMouse[1].mi.dwFlags = MOUSEEVENTF_RIGHTUP;

	_keyboard[0].type = INPUT_KEYBOARD;
	_keyboard[0].ki.dwFlags = 0;
	_keyboard[1].type = INPUT_KEYBOARD;
	_keyboard[1].ki.dwFlags = KEYEVENTF_KEYUP;
}

VIRTUALINPUT::~VIRTUALINPUT() {}

void VIRTUALINPUT::mouse(const char mouseKey) {
	if (mouseKey == 'l') 
		SendInput(2, _leftMouse, sizeof(INPUT));
	else if (mouseKey == 'r') 
		SendInput(2, _rightMouse, sizeof(INPUT));
	else 
		MessageBox(0, "WTF is the mouse?", 0, MB_OK);
}

void VIRTUALINPUT::keyboard(const char key) {
	if (key < 'A' || key > 'Z') 
		MessageBox(0, "WTF do you want to press?", 0, MB_OK);
	else {
		_keyboard[0].ki.wVk = _keyboard[1].ki.wVk = key;
		SendInput(2, _keyboard, sizeof(INPUT));
	}
}
