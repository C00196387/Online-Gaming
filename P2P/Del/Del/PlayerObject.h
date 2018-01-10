#pragma once

#include <iostream>
#include <string>
#include <chrono>

class PlayerObject
{
public:
	int x, y;
	std::string id;
	int r, g, b;
	bool alive;
	bool chaser;
	
	std::chrono::steady_clock::time_point startTime;
	std::chrono::steady_clock::time_point endTime;

	int speedModifier;

	std::string timeAlive;

	PlayerObject(int x, int y, std::string id, int r, int g, int b) 
	{
		this->x = x; this->y = y; this->id = id; this->r = r; this->g = g; this->b = b; alive = true; speedModifier = 1; startTime = std::chrono::high_resolution_clock::now();
	};
};