//
// Created by Braulio Lobo on 9/19/19.
//

#include <iostream>
#include <sstream>
#include "Point2.h"
#include "../../Tester.h"
#include "../figures3/Figure3.h"

float Point2::getAbscissa() const {
    return position.getAbscissa();
}

float Point2::getOrdinate() const {
    return position.getOrdinate();
}

Point2::Point2(Vector2 position){
    this->position = position;
}

Point2::Point2(float abscissa, float ordinate){
    this->position = Vector2(abscissa, ordinate);
}

Point2::~Point2() {
    if(Tester::DEBUG_DELET)
        std::cout << "Punto eliminado" << std::endl;
}

float Point2::getKey() {
    return getAbscissa();
}

std::string Point2::toString() {
    std::ostringstream ss;
    ss << "P(" << getAbscissa() << ", " << getOrdinate() << ")";
    std::string s(ss.str());
    return s;
}

std::string Point2::toGraphString(int PROJECTION_PLANE) {
    switch(PROJECTION_PLANE){
        case Figure3::PROJECTION_XY:
            return getStringCoordenateToGraph(getAbscissa(), getOrdinate(), 0);
        case Figure3::PROJECTION_XZ:
            return getStringCoordenateToGraph(getAbscissa(), 0, getOrdinate());
        case Figure3::PROJECTION_YZ:
            return getStringCoordenateToGraph(0, getAbscissa(), getOrdinate());
        default:
            return "Error de Point2_52";
    }
}


Point2::Point2() = default;


