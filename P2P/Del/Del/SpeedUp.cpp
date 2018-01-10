#include "SpeedUp.h"

SpeedUp::SpeedUp(int _x, int _y, std::string _id, int _width, int _height) {
	x = _x;
	y = _y;
	id = _id;
	width = _width;
	height = _height;

	alive = true;

	r = 244;
	g = 161;
	b = 66;

	modifier = 2;
}