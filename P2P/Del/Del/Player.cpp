#include "Player.h"

Player::Player()
{
	//Initialize the offsets
	mPosX = 0;
	mPosY = 0;

	//Initialize the velocity
	mVelX = 0;
	mVelY = 0;
}

Player::Player(int screenWidth, int screenHeight)
{
	//Initialize the offsets
	mPosX = 0;
	mPosY = 0;

	//Initialize the velocity
	mVelX = 0;
	mVelY = 0;

	mScreenWidth = screenWidth;
	mScreenHeight = screenHeight;
}

std::string Player::handleEvent(SDL_Event& e)
{

	return "NO";
}

void Player::move()
{
	//Move the dot left or right
	mPosX += mVelX;

	//If the dot went too far to the left or right
	if ((mPosX < 0) || (mPosX + mWidth > mScreenWidth))
	{
		//Move back
		mPosX -= mVelX;
	}

	//Move the dot up or down
	mPosY += mVelY;

	//If the dot went too far up or down
	if ((mPosY < 0) || (mPosY + mHeight > mScreenHeight))
	{
		//Move back
		mPosY -= mVelY;
	}
}

void Player::render(LTexture &gDotTexture, SDL_Renderer* gRenderer)
{
	//Show the dot
	gDotTexture.render(mPosX, mPosY, NULL, 0.0, NULL, SDL_FLIP_NONE, gRenderer);
}