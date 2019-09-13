#include <iostream>
#include "base/space/Vector.h"
#include "base/Manto.h"
#include "base/figures/Point.h"

int main() {
    Manto manto;

    Point* p = new Point(1, 1, 1);

    manto.addFigure(p);
    manto.addFigure(new Point(1, 2, 5));
    manto.addFigure(new Point(2, 3, 1));

    manto.printAllFigures();

    std::cout << p->toString() << std::endl;

    return 0;
}