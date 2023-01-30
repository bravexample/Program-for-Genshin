#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include <cstdlib>
#include <string>
#include <vector>
#include <algorithm>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "windows.h"

using namespace std;

class PROGRAM {
public:
	PROGRAM(const int, const int);
	~PROGRAM();
	void alloc_textures(const int);
	void load_image(const string &, const int);
	void render_texture(const int) const;
	void clean();
private:
	SDL_Window *_window = 0;
	SDL_Renderer *_renderer = 0;
	SDL_Surface *_surface = 0;
	vector<SDL_Texture *> _textureArray;
};

class VIRTUALINPUT {
public:
	VIRTUALINPUT();
	~VIRTUALINPUT();
	void mouse(const char);
	void keyboard(const char);
private:
	INPUT _leftMouse[2] = {};
	INPUT _rightMouse[2] = {};
	INPUT _keyboard[2] = {};
};

#endif