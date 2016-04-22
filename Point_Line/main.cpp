#include "Point.cpp"
#include "Line.cpp"
#include <iostream>
#include <iomanip>
using namespace std;

int main() {
	double x, y, a, b, c, _LL;
	Point p0, p1;
	Line l0, l1;
	p0 = Point(10, 10);
	p1 = Point(1, 1);
	l0 = Line(2, 4, -3);
	l1 = Line(1, 1, 1);
	cin >> x >> y >> a >> b >> c;
	p1.reset(x, y);
	l0.reset(a, b, c);

	cout << setprecision(2) << fixed << "distance between " << p0.display()
		<< " and " << p1.display() << " is " << dist_PP(p0, p1) << endl;
	cout << setprecision(2) << fixed << "distance between " << l0.display()
		<< " and " << p0.display() << " is " << dist_LP(l0, p0) << endl;
		
	_LL = dist_LL(l0, l1);
	if (_LL == -1) {
		cout << l0.display() << " and " << l1.display() << " is not parallel.\n";
	} else {
		cout << setprecision(2) << fixed << "distance between " << l0.display()
			<< " and " << l1.display() << " is " << _LL << endl;
	}

	return 0;
}

