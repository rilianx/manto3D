//
// Created by Braulio Lobo on 9/7/19.
//

#include <sstream>
#include <iostream>
#include "Point.h"

float Point::getX() const {
    return position.getX();
}
float Point::getY() const {
    return position.getY();
}
float Point::getZ() const {
    return position.getZ();
}

bool Point::dominate(Point point) const {
    float tx = this->getX();
    float ty = this->getY();
    float tz = this->getZ();
    float px = point.getX();
    float py = point.getY();
    float pz = point.getZ();
    return tx <= px && ty <= py && tz <= pz;
}

Point::Point(float x, float y, float z){
    this->position = Vector(x,y,z);
}

Point::Point(Vector vector) {
    this->position = vector;
}

std::string Point::toString() {
    std::ostringstream ss;
    ss << "P(" << getX() << ", " << getY() << ", " << getZ() << ")";
    std::string s(ss.str());
    return s;
}

Point::~Point() {
    std::cout << "Eliminado " << toString() << std::endl;
}


