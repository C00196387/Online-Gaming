#include "UserInput.h"

void UserInput::handleInput(SDL_Event &e)
{
	if (e.type == SDL_KEYDOWN)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_UP: 
			up = true; 
			break;
		case SDLK_DOWN: 
			down = true; 
			break;
		case SDLK_LEFT: 
			left = true; 
			break;
		case SDLK_RIGHT: 
			right = true; 
			break;
		default: 
			break;
		}
	}
	if (e.type == SDL_KEYUP)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_UP: 
			up = false; 
			break;
		case SDLK_DOWN: 
			down = false;
			break;
		case SDLK_LEFT: 
			left = false; 
			break;
		case SDLK_RIGHT: 
			right = false; 
			break;
		default: 
			break;
		}
	}
}