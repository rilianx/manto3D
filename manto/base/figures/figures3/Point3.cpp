//
// Created by Braulio Lobo on 9/19/19.
//

#include <iostream>
#include <sstream>
#include "Point3.h"
#include "Figure3.h"
#include <algorithm>
#include "../../Tester.h"

void Point3::generateProjections() {
    const int pxy = Figure3::PROJECTION_XY;
    const int pxz = Figure3::PROJECTION_XZ;
    const int pyz = Figure3::PROJECTION_YZ;
    projections[pxy] = Point2(position.getProjection(pxy));
    projections[pxz] = Point2(position.getProjection(pxz));
    projections[pyz] = Point2(position.getProjection(pyz));
}

float Point3::getX() const {
    return position.getX();
}

float Point3::getY() const {
    return position.getY();
}

float Point3::getZ() const {
    return position.getZ();
}

Point3::~Point3() {
    if(Tester::DEBUG_DELET)
        std::cout << "Destruido el punto 3D" << std::endl;
}

Point3::Point3(float x, float y, float z) {
    this->position = Vector3(x, y, z);
    generateProjections();
}

Point3::Point3(Vector3 position) {
    this->position = position;
    generateProjections();
}

Point2* Point3::getProjection(int PROJECTION_PLANE) {
    return &projections[PROJECTION_PLANE];
}

std::string Point3::toString() {
    std::ostringstream ss;
    ss << "P(" << getX() << ", " << getY() << ", " << getZ() << ")";
    std::string s(ss.str());
    return s;
}

std::string Point3::toGraphString() {
    std::ostringstream ss;
    ss << getX() << ";" <<
          getY() << ";" <<
          getZ();
    std::string s(ss.str());
    std::replace(s.begin(), s.end(), '.', ',');

    //std::cout << toString() << " == " << s << std::endl;
    return s;
}

bool Point3::equal(Point3* p) {
    return this->getX() == p->getX() &&
            this->getY() == p->getY() &&
            this->getZ() == p->getZ();
}

bool Point3::isDominated(Figure3* figure) {
    Point3* point;

    // Discriminando casso de la figura
    switch (figure->getInstance()){
        // Caso en que sea un punto
        case POINT_INSTANCE:
            point = dynamic_cast<Point3*>(figure);
            return point->getX() <= getX() && point->getY() <= getY()
                    && point->getZ() <= getZ();
        default:
            std::cout << "Error 0ad12: Caso no encontrado" << std::endl;
            break;
    }
    return false;
}

int Point3::getInstance() {
    return Figure3::POINT_INSTANCE;
}

bool Point3::equal(Figure3 *figure3) {
    if(figure3->getInstance() != this->getInstance())
        return false;
    Point3* p3 = dynamic_cast<Point3*>(figure3);
    return p3->getX() == this->getX() && p3->getY() == this->getY() &&
            p3->getZ() == this->getZ();
}

const Vector3 &Point3::getPosition() const {
    return position;
}
