#include <iostream>
#include "Vector.cpp"
#define MAX 51
using namespace std;

int main() {
    string name = "";
    int dim, num[MAX];
    Vector vec1, vec2, vec3;
    cin >> name >> dim;
    for (int i = 0; i < dim; i++) {
        cin >> num[i];
    }
    vec1 = Vector(name, dim, num);
    vec1.print();
    vec2 = Vector(vec1);
    vec2.print();
    vec1.isEqual(vec2);
    int vec3_num[] = {1, 2, 3};
    vec3 = Vector(name, 3, vec3_num);
    vec1.isEqual(vec3);
    vec2.setName("helloWorld!");
    vec1.isEqual(vec2);

    return 0;
}

