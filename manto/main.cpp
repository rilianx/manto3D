#include <iostream>
#include "base/Vector.h"

int main() {
    Vector vector = Vector(0, 1, 0);
    Vector vector2 = Vector(1, 0, 0);

    std::cout << vector2.crossProduct(vector).toString() << std::endl;

    return 0;
}