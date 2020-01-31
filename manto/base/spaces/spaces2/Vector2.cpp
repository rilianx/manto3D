//
// Created by Braulio Lobo on 9/18/19.
//

#include "Vector2.h"

Vector2::Vector2(float abscissa, float ordinate) {
    this->abscissa = abscissa;
    this->ordinate = ordinate;
}

float Vector2::getAbscissa() const {
    return this->abscissa;
}

float Vector2::getOrdinate() const {
    return this->ordinate;
}

Vector2::Vector2() {
    this->abscissa = 0;
    this->ordinate = 0;
}
