#pragma once

#include <iostream>
#include <string>

class PlayerObject
{
public:
	int x, y;
	std::string id;
	int r, g, b;
	bool alive;
	bool chaser;

	int speedModifier;

	PlayerObject(int x, int y, std::string id, int r, int g, int b) { this->x = x; this->y = y; this->id = id; this->r = r; this->g = g; this->b = b; alive = true; speedModifier = 1; };
};