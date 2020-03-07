//
// Created by Braulio Lobo on 25-02-20.
//

#include "Polygon3.h"
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
    projections[pxy] = Polygon2(vectoresXY, nVectors);
    projections[pxz] = Polygon2(vectoresXZ, nVectors);
    projections[pyz] = Polygon2(vectoresYZ, nVectors);
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



