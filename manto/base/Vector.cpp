//
// Created by Braulio Lobo on 9/6/19.
//

#include <sstream>
#include "Vector.h"

float Vector::getX() const{
    return x;
}

float Vector::getY() const{
    return y;
}

float Vector::getZ() const {
    return z;
}

Vector::Vector(float x, float y, float z) : x(x), y(y), z(z) {}

std::string Vector::toString() {
    std::ostringstream ss;
    ss << "(" << getX() << ", " << getY() << ", " << getZ() << ")";
    std::string s(ss.str());
    return s;
}

Vector Vector::crossProduct(const Vector vector) const {
    return {this->getY() * vector.getZ() - this->getZ() * vector.getY(),
            this->getZ() * vector.getX() - this->getX() * vector.getZ(),
            this->getX() * vector.getY() - this->getY() * vector.getX()};
}

float Vector::dotProduct(const Vector vector) const {
    return this->getX() * vector.getX() +
            this->getY() * vector.getY() +
            this->getZ() * vector.getZ();
}

bool Vector::equals(Vector vector) const {
    return this->getX() == vector.getX() &&
            this->getY() == vector.getY() &&
            this->getZ() == vector.getZ();
}


