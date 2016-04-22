#include "Vector.h"
#include <iostream>
#include <string.h>
#include <math.h>
using namespace std;

Vector::Vector() {
	x = y = 0;
}

Vector::Vector(int a, int b) {
	x = a;
	y = b;
}

Vector::Vector(const Vector &otherVec) {
	x = otherVec.x;
	y = otherVec.y;
}

Vector Vector::add(Vector v) {
	return Vector(x+v.x, y+v.y);
}

Vector Vector::sub(Vector v) {
	return Vector(x-v.x, y-v.y);
}

Vector Vector::inverse() {
	return Vector(-x, -y);
}

int Vector::dot_product(Vector v) {
	return x*v.x+y*v.y;
}

int Vector::cross_product(Vector v) {
	return abs(x*v.y-y*v.x);
}

void Vector::print() {
	cout << "(" << x << ", " << y << ")\n";
}

