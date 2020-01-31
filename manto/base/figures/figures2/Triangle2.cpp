//
// Created by Braulio Lobo on 25-01-20.
//

#include <spaces/spaces2/Line2.h>
#include <sstream>
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
    std::ostringstream ss;
    ss << "S(" << p1.getAbscissa() << ", " << p1.getOrdinate() << ")";
    ss << "->(" << p2.getAbscissa() << ", " << p2.getOrdinate() << ")";
    ss << "->(" << p3.getAbscissa() << ", " << p3.getOrdinate() << ")";
    std::string s(ss.str());
    return s;
}

std::string Triangle2::toGraphString(int PROJECTION_PLANE) {
    return std::string();
}

Triangle2::Triangle2() {}

Triangle2** Triangle2::split(Vector2 pl1, Vector2 pl2) {
    // Generando la linea que pasa por los puntos pl1 y pl2
    Line2 line = {pl1, pl2};

    std::list<Vector2*> puntos;   // Puntos de interseccion

    Vector2* pi1 = line.intersect(this->p1, this->p2);
    Vector2* pi2 = nullptr;

    Vector2* pInterseccion = line.intersect(this->p2, this->p3);
    if(pi1 != nullptr) pi2 = pInterseccion;
    else pi1 = pInterseccion;

    pInterseccion = line.intersect(this->p3, this->p1);
    if(pInterseccion != nullptr && pi1 != nullptr) pi2 = pInterseccion;

    if(pi2 == nullptr)
        return nullptr;


    Triangle2* t1 = new Triangle2(*pi1, *pi2, p1);
    Triangle2* t2 = new Triangle2(*pi1, *pi2, p2);
    Triangle2* t3 = new Triangle2(*pi1, *pi2, p3);

    Triangle2** triangles = new Triangle2*[3];
    triangles[0] = t1;
    triangles[1] = t2;
    triangles[2] = t3;

    return triangles;
}


