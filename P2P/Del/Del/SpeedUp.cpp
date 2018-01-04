#include "SpeedUp.h"

SpeedUp::SpeedUp() 
{
	mRect = { 0, 0, 10, 10 };
}

SpeedUp::SpeedUp(int x, int y)
{
	mRect = { x, y, 10, 10 };

	mColour = { 255, 160, 30 };

	mAlive = true;
}

void SpeedUp::setAlive(bool alive)
{
	mAlive = alive;
}

bool SpeedUp::getAlive()
{
	return mAlive;
}

void SpeedUp::render(LTexture &gDotTexture, SDL_Renderer* gRenderer)
{
	//Show the dot
	if (mAlive == true)
	{
		gDotTexture.setColor(mColour);
	}

	gDotTexture.render(mRect.x, mRect.y, NULL, 0.0, NULL, SDL_FLIP_NONE, gRenderer);
}
