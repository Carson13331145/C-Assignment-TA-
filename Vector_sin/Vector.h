#ifndef VECTOR_H
#define VECTOR_H
using namespace std;

class Vector {
	public:
		// constructer 
		Vector();
		Vector(int, int);
		// copy constructer
		Vector(const Vector &otherVec);
		// destructer
		~Vector() {}
		// vecter1 + vecter2
		Vector add(Vector);
		// vecter1 - vecter2
		Vector sub(Vector);
		// -vecter1
		Vector inverse();
		// vecter1 * vecter2
		int dot_product(Vector);
		// vecter1 x vecter2 
		int cross_product(Vector);
		// display the vecter
		void print();
	private:
		int x, y;
};

#endif

