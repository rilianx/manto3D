//
// Created by Braulio Lobo on 25-02-20.
//

#include "Polygon3.h"
#include "Segment3.h"
#include <algorithm>
#include <cfloat>
#include <sstream>
#include <iostream>
#include <spaces/spaces3/Line3.h>

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

std::list<Polygon3 *> Polygon3::fragment(Polygon3 *polygon3) {
    std::list<Polygon3 *> fragments;
    std::list<Polygon3 *> toFragment; // Lista de poligonos a fragmentar

    // Agregando este poligono para ser fragmentado
    toFragment.push_back(this);

    for (const auto &projection : Figure3::PROJECTIONS) {
        // Obteniendo proyecciones
        Polygon2* projPolygon = polygon3->getProjection(projection);

        // Creando lista de fragmentos en esta proyeccion
        std::list<Polygon2 *> proyFragments;
        std::list<Polygon2 *> temporalList;

        // Agregando valor inicial a la lista de fragmentos para esta proyeccion
        for(auto polygon : toFragment) {
            Polygon2 *projSelf = this->getProjection(projection);
            proyFragments.push_back(projSelf);
        }

        // Obteniendo limites de la zona dominada por el poligono ingresado
        Line2 line_lv = projPolygon->getLowerVLine();
        Line2 line_lh = projPolygon->getLowerHLine();

        // Fragmentando poligono con la linea vertical
        temporalList.clear();
        for (const auto &fragment : proyFragments) {
            for (const auto &newFragment : fragment->split(&line_lv)) {
                temporalList.push_back(newFragment);
            }
        }
        proyFragments = temporalList;

        // Fragmentando poligono con la linea horaizontal
        temporalList.clear();
        for (const auto &fragment : proyFragments) {
            for (const auto &newFragment : fragment->split(&line_lh)) {
                temporalList.push_back(newFragment);
            }
        }
        proyFragments = temporalList;

        // Fragmentando poligono con las lineas del otro poligono
        for (const auto &line : projPolygon->getLines()) {
            temporalList.clear();
            for (const auto &fragment : proyFragments) {
                for (const auto &newFragment : fragment->split(line)) {
                    temporalList.push_back(newFragment);
                }
            }
            proyFragments = temporalList;
        }

        // FIXME: esto es temporal (Borrar hasta el break)
        toFragment.clear();
        for (auto &proyFragment : proyFragments) {
            toFragment.push_back(proyFragment->toPolygon3(this, projection));
        }
        //break; // FIXME: borrar esto
    }

    // TODO: colocar aquí una forma de pasar de poligonos 2d a poligonos 3d

    // Fragmentando fragmentos resultantes por el plano generado por el
    // poligono fragmentador
    Plane plane = polygon3->getPlane();
    fragments.clear();
    for(auto fragment : toFragment){
        for(auto subFragment : fragment->split(plane)){
            fragments.push_back(subFragment);
        }
    }

    return fragments;
}

Point3 Polygon3::getAPoint() {
    Segment3 s1 = Segment3(this->vectors[0], this->vectors[1]);
    Vector3 m1 = s1.getMidlePoint();

    Segment3 s2 = Segment3(this->vectors[1], this->vectors[2]);
    Vector3 m2 = s2.getMidlePoint();

    Segment3 s3 = Segment3(m1, m2);
    Vector3 m3 = s3.getMidlePoint();

    // FIXME: iterar generando segmentos s2 con otras coordenadas para poder
    //  generar otro vector interior.
    if(!this->onPolygon(m3)){
        std::cout << "ERROR: VECTOR GENERADO FUERA DEL POLIGONO" << std::endl;
    }

    return Point3(m3);
}

std::list<Polygon3 *> Polygon3::split(Plane plane) {
    std::list<Polygon3 *> result;

    Line3* line3 = this->getPlane().intersect(plane);

    // Si no hay interseccion de los planos
    if(line3 == nullptr)
        return result;

    // Obteniendo proyecciones
    Polygon2* proj = this->getProjection(Figure3::PROJECTION_XY);
    Line2* line = line3->getProjection(Figure3::PROJECTION_XY);

    // Dividinedo proyecciones
    std::list<Polygon2 *> result2 = proj->split(line);

    // Obteniendo resultado en tres dimensiones
    for (auto &poly2 : result2) {
        Polygon3* poly3 = poly2->toPolygon3(this, poly2->PROJECTION_PLANE);
        result.push_back(poly3);
    }

    return result;
}

bool Polygon3::onPolygon(Vector3 v3) {
    Vector2 v2;
    Polygon2* p2;

    // Iterando todas las proyecciones
    for (auto &projection_id : Figure3::PROJECTIONS) {
        v2 = v3.getProjection(projection_id);
        p2 = this->getProjection(projection_id);

        if(!p2->onPolygon(v2)) return false;
    }
    return true;
}



