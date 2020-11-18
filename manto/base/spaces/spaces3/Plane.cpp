//
// Created by Braulio Lobo on 29-05-20.
//

#include "Plane.h"
#include "Line3.h"

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

Vector3 Plane::getClosestPointTo(Vector3 point) {
    Line3 line = Line3(getNormal(), point);
    return line.intersect(*this);
}

Line3* Plane::intersect(Plane plane) {
    Vector3 n1 = this->normal;
    Vector3 n2 = plane.normal;

    // Calculando vector director de la recta
    Vector3 director = {
            n1.getY() * n2.getZ() - n1.getZ() * n2.getY(),
            n1.getZ() * n2.getX() - n1.getX() * n2.getZ(),
            n1.getX() * n2.getY() - n1.getY() * n2.getX()
    };

    // Calculando punto por el que pasa la recta
    float a1 = a;
    float b1 = b;
    float c1 = c;
    float d1 = -d;
    float a2 = plane.a;
    float b2 = plane.b;
    float c2 = plane.c;
    float d2 = -plane.d;

    float det;
    float x, y, z;

    // Para z = 0
    det = a1 * b2 - a2 * b1;
    if(det != 0){
        x = (d1 * b2 - d2 * b1) / det;
        y = (a1 * d2 - a2 * d1) / det;
        z = 0;
        return new Line3(director, {x, y, z});
    }

    // Con y = 0
    det = a1 * c2 - a2 * c1;
    if(det != 0){
        x = (d1 * c2 - d2 * c1) / det;
        y = 0;
        z = (a1 * d2 - a2 * d1) / det;
        return new Line3(director, {x, y, z});
    }

    // Con x = 0
    det = b1 * c2 - b2 * c1;
    if(det != 0){
        x = 0;
        y = (d1 * c2 - d2 * c1) / det;
        z = (b1 * d2 - b2 * d1) / det;
        return new Line3(director, {x, y, z});
    }

    return nullptr;
}
