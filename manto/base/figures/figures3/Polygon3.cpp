//
// Created by Braulio Lobo on 25-02-20.
//

#include "Polygon3.h"
#include <algorithm>
#include <cfloat>
#include <sstream>
#include <iostream>

void Polygon3::generateProjections() {
    const int pxy = Figure3::PROJECTION_XY;
    const int pxz = Figure3::PROJECTION_XZ;
    const int pyz = Figure3::PROJECTION_YZ;

    float vectoresXY[nVectors*2];
    float vectoresXZ[nVectors*2];
    float vectoresYZ[nVectors*2];

    for(int i = 0; i < nVectors; i++){
        vectoresXY[i*2] = vectors[i].getX();
        vectoresXY[i*2+1] = vectors[i].getY();

        vectoresXZ[i*2] = vectors[i].getX();
        vectoresXZ[i*2+1] = vectors[i].getZ();

        vectoresYZ[i*2] = vectors[i].getY();
        vectoresYZ[i*2+1] = vectors[i].getZ();
    }

    // Asignando proyecciones
    projections[pxy] = Polygon2(vectoresXY, nVectors, pxy);
    projections[pxz] = Polygon2(vectoresXZ, nVectors, pxz);
    projections[pyz] = Polygon2(vectoresYZ, nVectors, pyz);
}

Polygon3::Polygon3(Vector3 *vectors, int nVectors) {
    this->vectors = static_cast<Vector3 *>(malloc(sizeof(Vector3) * nVectors));
    for (int i = 0; i < nVectors; ++i) {
        this->vectors[i] = vectors[i];
    }
    this->nVectors = nVectors;

    generateProjections();
}

Polygon3::Polygon3(std::list<Vector3> vectorsList, int nVectors) {
    this->vectors = static_cast<Vector3 *>(malloc(sizeof(Vector3) * nVectors));
    int i = 0;
    for (auto &vect : vectorsList) {
        this->vectors[i] = vect;
        i++;
    }
    this->nVectors = nVectors;

    generateProjections();
}

Polygon2 *Polygon3::getProjection(int PROJECTION_PLANE) {
    return &projections[PROJECTION_PLANE];
}

std::string Polygon3::toString() {
    std::ostringstream ss;
    ss << "Poly3:\n";
    for(int i = 0; i < nVectors; i++) {
        ss << "  (" << vectors[i].getX() << ", " <<
                       vectors[i].getY() << ", " <<
                       vectors[i].getZ() << ")\n";
    }

    std::string s(ss.str());
    return s;
}

std::string Polygon3::toGraphString() {
    std::ostringstream ss;

    // Agregando coordenadas a la cadena
    for(int i = 0; i < nVectors; i++){
        ss << vectors[i].getX() << ";" << vectors[i].getY() << ";" <<
        vectors[i].getZ();
        if(i+1 < nVectors)
            ss << ";";
    }

    std::string s(ss.str());
    std::replace(s.begin(), s.end(), '.', ',');

    return s;
}

bool Polygon3::isDominated(Figure3 *figure) {
    return false;
}

bool Polygon3::equal(Figure3 *figure3) {
    std::cout << "Probando dominacion de poligonos (Por hacer)" << std::endl;
    return false;
}

int Polygon3::getInstance() {
    return Figure3::POLYGON_INSTANCE;
}

Vector3 *Polygon3::getVectors() const {
    return vectors;
}

Polygon3::~Polygon3() {
}

Plane Polygon3::getPlane() {
    return Plane(vectors[0], vectors[1], vectors[2]);
}

bool Polygon3::domina(Point3 *figure) {
    Point2* pxy = figure->getProjection(Figure3::PROJECTION_XY);
    Point2* pxz = figure->getProjection(Figure3::PROJECTION_XZ);
    Point2* pyz = figure->getProjection(Figure3::PROJECTION_YZ);
    bool xy = projections[PROJECTION_XY].domina(*pxy, *figure, *this);
    bool xz = projections[PROJECTION_XZ].domina(*pxz, *figure, *this);
    bool yz = projections[PROJECTION_YZ].domina(*pyz, *figure, *this);
    return xy && xz && yz;
}

bool Polygon3::inBox(Point3 point3) {
    float x1 = FLT_MAX;
    float y1 = FLT_MAX;
    float z1 = FLT_MAX;
    float x2 = 0;
    float y2 = 0;
    float z2 = 0;

    for (int i = 0; i < nVectors; i++) {
        x1 = std::min(vectors[i].getX(), x1);
        y1 = std::min(vectors[i].getY(), y1);
        z1 = std::min(vectors[i].getZ(), z1);
        x2 = std::max(vectors[i].getX(), x2);
        y2 = std::max(vectors[i].getY(), y2);
        z2 = std::max(vectors[i].getZ(), z2);
    }

    return point3.getX() > x1 && point3.getX() < x2 &&
            point3.getZ() > z1 && point3.getZ() < z2 &&
            point3.getY() > y1 && point3.getY() < y2;
}



