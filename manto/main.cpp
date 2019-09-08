#include <iostream>
#include "base/Vector.h"
#include "base/Manto.h"
#include "base/figures/Point.h"

int main() {
    Manto manto;

    Point* p = new Point(1, 1, 1);

    manto.addFigura(p);
    manto.addFigura(new Point(1,2,5));
    manto.addFigura(new Point(2,3,1));

    manto.printAllFigures();

    std::cout << p->toString() << std::endl;

    return 0;
}