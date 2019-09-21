//
// Created by Braulio Lobo on 9/18/19.
//

#include <iostream>
#include "Vector3.h"
#include "../../figures/figures3/Figure3.h"

Vector2 Vector3::getProjection(const int PROJECTION_PLANE) {
    switch (PROJECTION_PLANE){
        case Figure3::PROJECTION_XY:
            return {this->x, this->y};
        case Figure3::PROJECTION_XZ:
            return {this->x, this->z};
        case Figure3::PROJECTION_YZ:
            return {this->y, this->z};
        default:
            std::cout << "Posible error 001" << std::endl;
            return {this->x, this->y};
    }
}

float Vector3::getX() const {
    return x;
}

float Vector3::getY() const {
    return y;
}

float Vector3::getZ() const {
    return z;
}

Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
