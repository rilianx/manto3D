//
// Created by Braulio Lobo on 9/19/19.
//

#include <iostream>
#include <sstream>
#include "Point3.h"
#include "Figure3.h"
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
    ss << (int)getX() << "," <<  Tester::p_fraccionaria(getX()) << ";" <<
          (int)getY() << "," <<  Tester::p_fraccionaria(getY()) << ";" <<
          (int)getZ() << "," <<  Tester::p_fraccionaria(getZ());
    std::string s(ss.str());
    return s;
}
