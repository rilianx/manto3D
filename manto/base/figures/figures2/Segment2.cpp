//
// Created by Braulio Lobo on 11-10-19.
//

#include <Tester.h>
#include <iostream>
#include "Segment2.h"

std::string Segment2::toGraphString(int PROYECTION_PLANE) {
    // TODO: prorgramar toHraphString para segment2
    return std::string();
}

std::string Segment2::toString() {
    // TODO: programar toString segment2
    return std::string();
}

float Segment2::getKey() {
    return std::min(p1.getAbscissa(), p2.getAbscissa());
}

Segment2::Segment2(float ab1, float or1, float ab2, float or2) {
    this->p1 = Vector2(ab1, or1);
    this->p2 = Vector2(ab2, or2);
}

Segment2::Segment2(Vector2 p1, Vector2 p2) {
    this->p1 = p1;
    this->p2 = p2;
}

Segment2::Segment2() {

}

Segment2::~Segment2() {
    if(Tester::DEBUG_DELET){
        std::cout << "Punto eliminado" << std::endl;
    }
}

const Vector2 &Segment2::getP1() const {
    return p1;
}

const Vector2 &Segment2::getP2() const {
    return p2;
}

float Segment2::getDelta(Vector2 p) {
    float delta = (p.getAbscissa() - p1.getAbscissa()) /
            (p2.getAbscissa() - p1.getAbscissa());
    return delta;
}

