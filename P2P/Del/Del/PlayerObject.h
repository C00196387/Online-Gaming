#pragma once

#include <iostream>
#include <string>

class PlayerObject
{
public:
	int x, y;
	std::string id;
	std::string color;
	PlayerObject(int x, int y, std::string id) { this->x = x; this->y = y; this->id = id;  color = "BLUE"; };
};