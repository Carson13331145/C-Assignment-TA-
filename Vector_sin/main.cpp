#include <iostream>
#include "Vector.cpp"
using namespace std;

int main() {
	//	test#
	int x1, y1, x2, y2;
	cin >> x1 >> y1 >> x2 >> y2; 
	Vector vec1(x1, y1);
	Vector vec2(x2, y2);
	Vector vec3 = vec1.add(vec2);
	vec3.print();
	Vector vec4 = vec1.sub(vec2);
	vec4.print();
	Vector vec5 = vec1.inverse();
	vec5.print();
	int dot_result = vec1.dot_product(vec2);
	cout << "dot product equal:" << dot_result << ".\n";
	int cross_result = vec1.cross_product(vec2);
	cout << "cross product equal:" << cross_result << ".\n";

	return 0;
}

