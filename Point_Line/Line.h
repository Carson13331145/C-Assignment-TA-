#ifndef LINE_H
#define LINE_H
#include "Point.h"
#include <iostream>
#include <string.h>
using namespace std;

class Line {
	public:
		double a, b, c;
		Line();
		Line(double, double, double);
		~Line() {}
		void reset(const double &, const double &, const double &);
		string display();
		friend double dist_LP(const Line &, const Point &);
		friend double dist_LL(const Line &, const Line &);
};

#endif

