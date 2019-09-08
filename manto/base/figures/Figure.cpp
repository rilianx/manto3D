//
// Created by Braulio Lobo on 9/7/19.
//

#include <iostream>
#include "Figure.h"

Figure::~Figure() {
    std::cout << "Eliminado " << toString() << std::endl;
}
