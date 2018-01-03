#pragma once

#include "LTexture.h"

//The dot that will move around on the screen
class Player
{
public:
	//The dimensions of the dot
	static const int mWidth = 20;
	static const int mHeight = 20;

	int mScreenWidth = 640;
	int mScreenHeight = 480;

	//Maximum axis velocity of the dot
	static const int vel = 10;

	//Initializes the variables
	Player();

	Player(int screenWidth, int screenHeight);

	//Takes key presses and adjusts the dot's velocity
	std::string handleEvent(SDL_Event& e);

	//Moves the dot
	void move();

	//Shows the dot on the screen
	void render(LTexture &gDotTexture, SDL_Renderer* gRenderer);

	//The X and Y offsets of the dot
	int mPosX, mPosY;

	//The velocity of the dot
	int mVelX, mVelY;
};