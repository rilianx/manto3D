//
// Created by Braulio Lobo on 29-05-20.
//

#include "Plane.h"

Plane::Plane(const Vector3& p1, const Vector3& p2, const Vector3& p3) {
    // Calculando vectores directores
    vd1 = {p2.getX() - p1.getX(), p2.getY() - p1.getY(), p2.getZ() - p1.getZ()};
    vd2 = {p3.getX() - p1.getX(), p3.getY() - p1.getY(), p3.getZ() - p1.getZ()};

    // Guardando punto por el que pasa el plano
    point = p1;

    // Calculando normal
    normal = {
            vd1.getY() * vd2.getZ() - vd1.getZ() * vd2.getY(),
            vd1.getZ() * vd2.getX() - vd1.getX() * vd2.getZ(),
            vd1.getX() * vd2.getY() - vd1.getY() * vd2.getX()
    };

    // Calculando valores de la ecuacion general del plano
    a = normal.getX();
    b = normal.getY();
    c = normal.getZ();
    d = - point.getX() * normal.getX() - point.getY() * normal.getY() -
            point.getZ() * normal.getZ();
}

const Vector3 &Plane::getVd1() const {
    return vd1;
}

const Vector3 &Plane::getVd2() const {
    return vd2;
}

const Vector3 &Plane::getPoint() const {
    return point;
}

const Vector3 &Plane::getNormal() const {
    return normal;
}

float Plane::getA() const {
    return a;
}

float Plane::getB() const {
    return b;
}

float Plane::getC() const {
    return c;
}

float Plane::getD() const {
    return d;
}
