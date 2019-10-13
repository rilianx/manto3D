//
// Created by Braulio Lobo on 9/18/19.
//

#include <sstream>
#include "Figure2.h"
#include "../../Tester.h"

std::string Figure2::getStringCoordenateToGraph(float x, float y, float z) {
    std::ostringstream ss;
    ss << (int)x << "," <<  Tester::p_fraccionaria(x) << ";" <<
       (int)y << "," <<  Tester::p_fraccionaria(y) << ";" <<
       (int)z << "," <<  Tester::p_fraccionaria(z);
    std::string s(ss.str());
    return s;
}

bool Figure2::isDominated() const {
    return dominated;
}

void Figure2::setDominated(bool dominated) {
    Figure2::dominated = dominated;
}
