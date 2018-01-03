#include "Player.h"

Player::Player()
{
	//Initialize the offsets
	//mPosX = 0;
	//mPosY = 0;

	mRect = { 0, 0, 10, 10 };

	//Initialize the velocity
	mVelX = 0;
	mVelY = 0;
}

Player::Player(int screenWidth, int screenHeight, std::string team)
{
	//Initialize the offsets
	//mPosX = 0;
	//mPosY = 0;

	mRect = { 0, 0, 10, 10 };

	//Initialize the velocity
	mVelX = 0;
	mVelY = 0;

	mScreenWidth = screenWidth;
	mScreenHeight = screenHeight;

	mTeam = team;

	if (team == "red") 
	{
		mColour = { 255, 0, 0 };
		mDeadColour = { 150, 60, 60 };
	}
	else
	{
		mColour = { 0, 0, 255 };
		mDeadColour = { 60, 60, 150 };
	}

	mAlive = true;
}

std::string Player::handleEvent(SDL_Event& e)
{

	return "NO";
}

void Player::move()
{
	//Move the dot left or right
	mRect.x += mVelX;

	//If the dot went too far to the left or right
	if ((mRect.x < 0) || (mRect.x + mRect.w > mScreenWidth))
	{
		//Move back
		mRect.x -= mVelX;
	}

	//Move the dot up or down
	mRect.y += mVelY;

	//If the dot went too far up or down
	if ((mRect.y < 0) || (mRect.y + mRect.h > mScreenHeight))
	{
		//Move back
		mRect.y -= mVelY;
	}
}

void Player::render(LTexture &gDotTexture, SDL_Renderer* gRenderer)
{
	//Show the dot
	if (mAlive == true)
	{
		gDotTexture.setColor(mColour);
	}
	else
	{
		gDotTexture.setColor(mDeadColour);
	}
	gDotTexture.render(mRect.x, mRect.y, NULL, 0.0, NULL, SDL_FLIP_NONE, gRenderer);
}

void Player::checkIntersection(SDL_Rect rect) 
{
	if (SDL_IntersectRect(&mRect, &rect, new SDL_Rect{ 0,0,0,0 }))
	{
		mAlive = false;
	}
}