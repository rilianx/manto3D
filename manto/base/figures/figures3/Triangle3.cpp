//
// Created by Braulio Lobo on 25-01-20.
//

#include <sstream>
#include <iostream>
#include <algorithm>
#include "Triangle3.h"

Triangle3::Triangle3(float p1x, float p1y, float p1z, float p2x, float p2y,
                     float p2z, float p3x, float p3y, float p3z) {
    this->p1 = Vector3(p1x, p1y, p1z);
    this->p2 = Vector3(p2x, p2y, p2z);
    this->p3 = Vector3(p3x, p3y, p3z);
    generateProjections();
}

Triangle3::Triangle3(Vector3 p1, Vector3 p2, Vector3 p3) {
    this->p1 = p1;
    this->p2 = p2;
    this->p3 = p3;
    generateProjections();
}

bool Triangle3::isDominated(Figure3 *figure) {
    std::cout << "Probando dominancia (Triangulo)" << std::endl;
    return false;
}

std::string Triangle3::toGraphString() {
    std::ostringstream ss;
    ss << p1.getX() << ";" <<
       p1.getY() << ";" <<
       p1.getZ() << ";" <<
       p2.getX() << ";" <<
       p2.getY() << ";" <<
       p2.getZ() << ";" <<
       p3.getX() << ";" <<
       p3.getY() << ";" <<
       p3.getZ();
    std::string s(ss.str());

    std::replace(s.begin(), s.end(), '.', ',');

    return s;
}

std::string Triangle3::toString() {
    std::ostringstream ss;
    ss << "T(" << p1.getX() << ", " << p1.getY() << ", " << p1.getZ() << ")";
    ss << "->(" << p2.getX() << ", " << p2.getY() << ", " << p2.getZ() << ")";
    ss << "->(" << p3.getX() << ", " << p3.getY() << ", " << p3.getZ() << ")";
    std::string s(ss.str());
    return s;
}

Triangle2 *Triangle3::getProjection(int PROJECTION_PLANE) {
    return &projections[PROJECTION_PLANE];
}

int Triangle3::getInstance() {
    return Figure3::TRIANGLE_INSTANCE;
}

bool Triangle3::equal(Figure3 *figure3) {
    if(figure3->getInstance() != Figure3::TRIANGLE_INSTANCE)
        return false;

    // Haciendo cast del triangulo ingresado
    Triangle3 *t3 = dynamic_cast<Triangle3*>(figure3);

    // Obteniendo puntos
    // TODO: hacer comparacion de puntos (Puede que no sea necesario)

    return false;
}

void Triangle3::generateProjections() {
    const int pxy = Figure3::PROJECTION_XY;
    const int pxz = Figure3::PROJECTION_XZ;
    const int pyz = Figure3::PROJECTION_YZ;
    projections[pxy] = Triangle2(p1.getX(), p1.getY(), p2.getX(), p2.getY(),
            p3.getX(), p3.getY());
    projections[pxz] = Triangle2(p1.getX(), p1.getZ(), p2.getX(), p2.getZ(),
            p3.getX(), p3.getZ());
    projections[pyz] = Triangle2(p1.getY(), p1.getZ(), p2.getY(), p2.getZ(),
            p3.getY(), p3.getZ());
}
