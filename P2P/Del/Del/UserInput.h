#pragma once

#include <SDL.h>

class UserInput
{
public:
	UserInput() {}

	void handleInput(SDL_Event &e);

	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;
};