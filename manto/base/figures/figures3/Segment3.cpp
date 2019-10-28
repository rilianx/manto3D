//
// Created by Braulio Lobo on 10-10-19.
//

#include <sstream>
#include <Tester.h>
#include <iostream>
#include "Segment3.h"

Segment3::Segment3(Vector3 p1, Vector3 p2){
    this->p1 = p1;
    this->p2 = p2;
    generateProjections();
}

Segment3::Segment3(float p1x, float p1y, float p1z, float p2x, float p2y,
                   float p2z) {
    this->p1 = Vector3(p1x, p1y, p1z);
    this->p2 = Vector3(p2x, p2y, p2z);
    generateProjections();
}

float Segment3::getMenorX() {
    if(p1.getX() < p2.getX())
        return p1.getX();
    return p2.getX();
}

float Segment3::getMenorY() {
    if(p1.getY() < p2.getY())
        return p1.getY();
    return p2.getY();
}

float Segment3::getMenorZ() {
    if(p1.getZ() < p2.getZ())
        return p1.getZ();
    return p2.getZ();
}

float Segment3::getMaxX() {
    if(p1.getX() > p2.getX())
        return p1.getX();
    return p2.getX();
}

float Segment3::getMaxY() {
    if(p1.getY() > p2.getY())
        return p1.getY();
    return p2.getY();
}

float Segment3::getMaxZ() {
    if(p1.getZ() > p2.getZ())
        return p1.getZ();
    return p2.getZ();
}

bool Segment3::equal(Segment3 *segment) {
    return this->getMenorX() == segment->getMenorX() &&
           this->getMenorY() == segment->getMenorY() &&
           this->getMenorZ() == segment->getMenorZ() &&
           this->getMaxX()   == segment->getMaxX() &&
           this->getMaxY()   == segment->getMaxY() &&
           this->getMaxZ()   == segment->getMaxZ();
}

Segment2 *Segment3::getProjection(int PROJECTION_PLANE) {
    return &projections[PROJECTION_PLANE];
}

std::string Segment3::toString() {
    std::ostringstream ss;
    ss << "S(" << p1.getX() << ", " << p1.getY() << ", " << p1.getZ() << ")";
    ss << "->(" << p2.getX() << ", " << p2.getY() << ", " << p2.getZ() << ")";
    std::string s(ss.str());
    return s;
}

std::string Segment3::toGraphString() {
    std::ostringstream ss;
    ss << (int)p1.getX() << "," <<  Tester::p_fraccionaria(p1.getX()) << ";" <<
       (int)p1.getY() << "," <<  Tester::p_fraccionaria(p1.getY()) << ";" <<
       (int)p1.getZ() << "," <<  Tester::p_fraccionaria(p1.getZ()) << ";" <<
       (int)p2.getX() << "," <<  Tester::p_fraccionaria(p2.getX()) << ";" <<
       (int)p2.getY() << "," <<  Tester::p_fraccionaria(p2.getY()) << ";" <<
       (int)p2.getZ() << "," <<  Tester::p_fraccionaria(p2.getZ());
    std::string s(ss.str());
    return s;
}

Segment3::~Segment3() {
    if(Tester::DEBUG_DELET)
        std::cout << "Destruido el punto 3D" << std::endl;
}

void Segment3::generateProjections() {
    const int pxy = Figure3::PROJECTION_XY;
    const int pxz = Figure3::PROJECTION_XZ;
    const int pyz = Figure3::PROJECTION_YZ;
    projections[pxy] = Segment2(p1.getX(), p1.getY(), p2.getX(), p2.getY());
    projections[pxz] = Segment2(p1.getX(), p1.getZ(), p2.getX(), p2.getZ());
    projections[pyz] = Segment2(p1.getY(), p1.getZ(), p2.getY(), p2.getZ());
}
