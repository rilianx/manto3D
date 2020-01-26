//
// Created by Braulio Lobo on 25-01-20.
//

#include "Triangle2.h"



const Vector2 &Triangle2::getP11() const {
    return p1;
}

const Vector2 &Triangle2::getP21() const {
    return p2;
}

const Vector2 &Triangle2::getP3() const {
    return p3;
}

Triangle2::Triangle2(const Vector2 &p1, const Vector2 &p2, const Vector2 &p3)
        : p1(p1), p2(p2), p3(p3) {}

Triangle2::Triangle2(float p1a, float p1o, float p2a, float p2o, float p3a,
                     float p3o) {

}

float Triangle2::getKey() {
    return 0;
}

std::string Triangle2::toString() {
    return std::string();
}

std::string Triangle2::toGraphString(int PROJECTION_PLANE) {
    return std::string();
}

Triangle2::Triangle2() {

}
