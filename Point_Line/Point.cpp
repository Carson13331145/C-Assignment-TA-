#include "Point.h"
#include <stdlib.h>
#include <sstream>

Point::Point() {
	x = y = 0;
}

Point::Point(double _X, double _Y) {
	x = _X;
	y = _Y;
}

void Point::reset(const double &_X, const double &_Y) {
	x = _X;
	y = _Y;
}

string Point::display() {
	stringstream x_s, y_s;
	x_s << x;
	y_s << y;
	string str = "("+x_s.str()+", "+y_s.str()+")";
	return str;
}

double dist_PP(const Point &_P1, const Point &_P2) {
	return abs((_P1.x-_P2.x)*(_P1.x-_P2.x)+(_P1.y-_P2.y)*(_P1.y-_P2.y));
}

