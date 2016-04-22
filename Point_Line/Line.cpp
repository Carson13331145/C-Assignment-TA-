#include "Line.h"
#include <stdlib.h>
#include <sstream>
#include <cmath>

Line::Line() {
	a = b = c = 0;
}

Line::Line(double _A, double _B, double _C) {
	a = _A;
	b = _B;
	c = _C;
}

void Line::reset(const double &_A, const double &_B, const double &_C) {
	a = _A;
	b = _B;
	c = _C;
}

string Line::display() {
	string str = "";
	stringstream a_s, b_s, c_s;
	a_s << a;
	b_s << b;
	c_s << c;
	if (a != 0) str += a_s.str()+"x";
	if (b < 0) str += b_s.str()+"y";
	else if (a != 0 && b > 0) str += "+"+b_s.str()+"y";
	else if (b > 0) str += b_s.str()+"y"; 
	if (c < 0) str += c_s.str();
	else str += "+"+c_s.str();
	str += "=0";
	return str;
}

double dist_LP(const Line &_L, const Point &_P) {
	return abs((_L.a*_P.x+_L.b*_P.y+_L.c)/sqrt(_L.a*_L.a+_L.b*_L.b));
}

double dist_LL(const Line &_L1, const Line &_L2) {
	if (_L1.a/_L1.b != _L2.a/_L2.b) {
		return -1;
	}
	return abs((_L1.c-_L2.c*_L1.a/_L2.a)/sqrt(_L1.a*_L1.a+_L1.b*_L1.b));
}

