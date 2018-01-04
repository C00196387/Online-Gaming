#pragma once

#include "LTexture.h"

class SpeedUp
{
public:
	SpeedUp();
	SpeedUp(int x, int y);

	void setAlive(bool alive);
	bool getAlive();

	std::string id;

	void render(LTexture &gDotTexture, SDL_Renderer* gRenderer);

private:
	SDL_Rect mRect;
	SDL_Color mColour;
	bool mAlive;
};