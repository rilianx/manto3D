//
// Created by Braulio Lobo on 02-02-20.
//

#include "Polygon2.h"
#include "Polygon3.h"
#include <utility>
#include <sstream>
#include <iostream>


Polygon2::Polygon2(const int *vectores, int nVectores) {
    this->path.resize(nVectores);
    for (int i = 0; i < nVectores; i++) {
        this->path[i].X = vectores[i * 2] * precision;
        this->path[i].Y = vectores[i * 2 + 1] * precision;
    }
}

Polygon2::Polygon2(const float *vectores, int nVectores) {
    this->path.resize(nVectores);
    for (int i = 0; i < nVectores; i++) {
        this->path[i].X = vectores[i * 2] * precision;
        this->path[i].Y = vectores[i * 2 + 1] * precision;
    }
}

Polygon2::Polygon2(Path path) {
    this->path = std::move(path);
}

const Path &Polygon2::getPath() const {
    return path;
}

list<Polygon2*> Polygon2::intersect(const Polygon2& polygon) {
    Clipper clpr;

    clpr.Clear();
    clpr.AddPath(this->getPath(), ptSubject, true);
    clpr.AddPath(polygon.getPath(), ptClip, true);
    clpr.Execute(ctIntersection, solutions, pftEvenOdd, pftEvenOdd);

    return pathsToPolygons(solutions);
}

list<Polygon2*> Polygon2::unionWith(const Polygon2& polygon) {
    Clipper clpr;
    Paths solucion;

    clpr.Clear();
    clpr.AddPath(this->getPath(), ptSubject, true);
    clpr.AddPath(polygon.getPath(), ptClip, true);
    clpr.Execute(ctUnion, solutions, pftEvenOdd, pftEvenOdd);

    return pathsToPolygons(solutions);
}

list<Polygon2*> Polygon2::difference(const Polygon2& polygon) {
    Clipper clpr;
    Paths solucion;

    clpr.Clear();
    clpr.AddPath(this->getPath(), ptSubject, true);
    clpr.AddPath(polygon.getPath(), ptClip, true);
    clpr.Execute(ctDifference, solutions, pftEvenOdd, pftEvenOdd);

    return pathsToPolygons(solutions);
}

list<Polygon2*> Polygon2::pathsToPolygons(const Paths& paths) {
    list<Polygon2*> polygons;
    for (auto &pathInPaths : paths) {
        polygons.push_back(new Polygon2(pathInPaths));
    }
    return polygons;
}

float Polygon2::getKey() {
    return 0;
}

std::string Polygon2::toGraphString(int PROJECTION_PLANE) {
    // TODO: hacer el to graphstring para polygon2
    return std::string();
}

std::string Polygon2::toString() {
    std::ostringstream ss;
    ss << "Poly2:\n";
    for (auto &vect2 : path) {
        ss << "  (" << vect2.X/precision << ", " << vect2.Y/precision << ")\n";
    }

    std::string s(ss.str());
    return s;
}

Polygon2::Polygon2() {

}

void Polygon2::fragmentedBy(Point2 *p, std::list<Figure2 *> &fragments) {
    const int MAX_VALUE = 99999;
    float vectores[8] = {
            p->getAbscissa(), p->getOrdinate(),
            p->getAbscissa(), MAX_VALUE,
            MAX_VALUE, MAX_VALUE,
            MAX_VALUE, p->getOrdinate()
    };
    Polygon2* polygon2 = new Polygon2(vectores, 4);

    // Fragmentando y llendando la lista de fragmentos
    for (auto &fragment : this->difference(*polygon2)) {
        fragments.push_back(fragment);
    }
}

void Polygon2::fragmentedBy(Segment2 *s, std::list<Figure2 *> &fragments) {

}

void Polygon2::fragmentedBy(Triangle2 *t, std::list<Figure2 *> &fragments) {

}

void Polygon2::fragmentedBy(Polygon2 *p, std::list<Figure2 *> &fragments) {

}

Polygon3* Polygon2::toPolygon3(Polygon3* p3, int PROJECTION_PLANE) {
    // Vectores generadores
    Vector3 A = {p3->getVectors()[1].getX() - p3->getVectors()[0].getX(),
                 p3->getVectors()[1].getY() - p3->getVectors()[0].getY(),
                 p3->getVectors()[1].getZ() - p3->getVectors()[0].getZ()};
    Vector3 B = {p3->getVectors()[2].getX() - p3->getVectors()[0].getX(),
                 p3->getVectors()[2].getY() - p3->getVectors()[0].getY(),
                 p3->getVectors()[2].getZ() - p3->getVectors()[0].getZ()};
    // Vector normal
    Vector3 N = {A.getY()*B.getZ() - A.getZ()*B.getY(),
                 A.getZ()*B.getX() - A.getX()*B.getZ(),
                 A.getX()*B.getY() - A.getY()*B.getX()};

    // Punto que pasa por el plano
    Vector3 p = p3->getVectors()[0];

    // Lista de vectores
    std::list<Vector3> vectoresList;

    // Vector proyectado en el plano del poligono p3
    int index = 0;
    float x;
    float y;
    float z;
    for (auto &vector : path) {
        switch(PROJECTION_PLANE){
            case Figure3::PROJECTION_XY:
                x = vector.X/precision;
                y = vector.Y/precision;
                z = (-x*N.getX() + p.getX()*N.getX() - y*N.getY() + p
                        .getY()*N.getY()+p.getZ()*N.getZ())/N.getZ();
                break;
            case Figure3::PROJECTION_XZ:
                x = vector.X/precision;
                z = vector.Y/precision;
                y = (-x*N.getX() + p.getX()*N.getX() + p.getY()*N.getY() -
                        z*N.getZ() + p.getZ()*N.getZ())/N.getY();
                break;
            case Figure3::PROJECTION_YZ:
                y = vector.X/precision;
                z = vector.Y/precision;
                x = (p.getX()*N.getX() - y*N.getY() + p.getY()*N.getY() - z*N
                        .getZ() + p.getZ()*N.getZ())/N.getX();
                break;
            default:
                std::cout << "Error 8912eyujksdhfiuo2y3e" << std::endl;
                return nullptr;
        }

        vectoresList.emplace_back(x,y,z);
        index++;

    }

    return new Polygon3(vectoresList, path.size());
}
