#ifndef POINT_H
#define POINT_H
#include <iostream>
#include <string.h>
using namespace std;

class Point {
	public:
		double x, y;
		Point();
		Point(double, double);
		~Point() {}
		void reset(const double &, const double &);
		string display();
		friend double dist_PP(const Point &, const Point &);
};

#endif

