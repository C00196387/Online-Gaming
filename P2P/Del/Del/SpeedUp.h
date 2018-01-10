#pragma once

#include <iostream>
#include <string>

class SpeedUp {
public:
	SpeedUp(int _x, int _y, std::string _id, int _width, int _height);

	std::string id;

	int x;
	int y;

	int modifier;

	int r;
	int g;
	int b;

	int width;
	int height;

	bool alive;
};