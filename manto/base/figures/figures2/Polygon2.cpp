//
// Created by Braulio Lobo on 02-02-20.
//

#include "Polygon2.h"
#include "Polygon3.h"
#include "Segment2.h"
#include <utility>
#include <sstream>
#include <iostream>
#include "util/IndexIterator.h"

using namespace ClipperLib;
using namespace std;

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
    float vectores[8] = {
            p->getAbscissa(), p->getOrdinate(),
            p->getAbscissa(), MAX_VALUE,
            MAX_VALUE, MAX_VALUE,
            MAX_VALUE, p->getOrdinate()
    };
    Polygon2* polygon2 = new Polygon2(vectores, 4);

    // Fragmentando y llenando la lista de fragmentos
    for (auto &fragment : this->difference(*polygon2)) {
        fragments.push_back(fragment);
    }
}

void Polygon2::fragmentedBy(Segment2 *s, std::list<Figure2 *> &fragments) {
    // Obteniendo puntos
    Vector2 pp1 = s->getMenorAbscissa();
    Vector2 pp2 = s->getMayorAbscissa();

    // generando vertices del poligono de fragmentación
    float vectores[10] = {
            pp1.getAbscissa(), MAX_VALUE,
            MAX_VALUE, MAX_VALUE,
            MAX_VALUE, pp2.getOrdinate(),
            pp2.getAbscissa(), pp2.getOrdinate(),
            pp1.getAbscissa(), pp1.getOrdinate()
    };

    // Generando poligono
    Polygon2* polygon2 = new Polygon2(vectores, 5);

    // Fragmentando y llenando la lista de fragmentos
    for (auto &fragment : this->difference(*polygon2)) {
        fragments.push_back(fragment);
    }

    delete(polygon2);
}

void Polygon2::fragmentedBy(Triangle2 *t, std::list<Figure2 *> &fragments) {

}

void Polygon2::fragmentedBy(Polygon2 *p, std::list<Figure2 *> &fragments) {
    // TODO: programar la fragmentacion de poligono poligono
    // Obteniendo puntos inferiores del poligono
    std::list<Vector2> bottomPath = p->getBottomPath();

    // Realmente nVectores es el numero de vectores * 2
    unsigned long int nVectores = bottomPath.size() * 2 + 6;
    float minAbscissa = p->getAbscissa(p->getMenorAbscissa());
    float minOrdinate = p->getOrdinate(p->getMenorOrdinate());

    // Construyendo vectores del poligono de interseccion
    float vectores[nVectores];
    int i = 0;
    for (auto &vector : bottomPath) {
        vectores[i++] = vector.getAbscissa();
        vectores[i++] = vector.getOrdinate();
    }
    vectores[i++] = MAX_VALUE;
    vectores[i++] = minOrdinate;
    vectores[i++] = MAX_VALUE;
    vectores[i++] = MAX_VALUE;
    vectores[i++] = minAbscissa;
    vectores[i] = MAX_VALUE;

    // Generando poligono
    Polygon2* polygon2 = new Polygon2(vectores, nVectores/2);

    // Fragmentando y llenando la lista de fragmentos
    for (auto &fragment : this->difference(*polygon2)) {
        fragments.push_back(fragment);
    }

    delete(polygon2);
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

float Polygon2::getAbscissa(int index) {
    return path[index].X / precision;
}

float Polygon2::getOrdinate(int index) {
    return path[index].Y / precision;
}

int Polygon2::getMenorAbscissa() {
    float menorAbscisa = MAX_VALUE;
    float ordinate = MAX_VALUE;
    int index = -1;
    for (int i = 0; i < path.size(); i++) {
        float abscisa = getAbscissa(i);
        if(abscisa < menorAbscisa){
            menorAbscisa = abscisa;
            ordinate = getOrdinate(i);
            index = i;
        }

        // Caso especial en que el nuevo vector se encuentra en la vertical
        else if(abscisa == menorAbscisa && ordinate < getOrdinate(i)){
            index = i;
        }

        if(abscisa < menorAbscisa) {
            menorAbscisa = abscisa;
            index = i;
        }

    }

    if(index == -1){
        throw "No se pudo obtener el valor minimo de la abscissa";
    }
    return index;
}

int Polygon2::getMenorOrdinate() {
    float menorOrdenada = MAX_VALUE;
    float abscisa = MAX_VALUE;
    int index = -1;
    for (int i = 0; i < path.size(); i++){
        float ordenada = getOrdinate(i);
        if(ordenada < menorOrdenada){
            menorOrdenada = ordenada;
            abscisa = getAbscissa(i);
            index = i;
        }

        // Caso especial en que el nuevo vector se encuentra en la horizontal
        else if(ordenada == menorOrdenada && abscisa < getAbscissa(i)){
            index = i;
        }
    }

    if(index == -1){
        throw "No se pudo obtener el valor minimo de la abscissa";
    }

    return index;
}

std::list<Vector2> Polygon2::getBottomPath() {
    std::list<Vector2> result;

    // Seleccionando vector inicial y final
    int indexInit = getMenorAbscissa();
    int indexEnd = getMenorOrdinate();

    // Calculando valor del iterador
    IndexIterator ii = IndexIterator(indexInit, path.size()-1);

    // Pendientes
    float mNext; // Pendiente si avanzo
    float mBack; // Pendiente si retrocedo

    float y1 = getOrdinate(indexInit);
    float x1 = getAbscissa(indexInit);

    // Avanzando
    ii.next();
    float y2 = getOrdinate(ii.get());
    float x2 = getAbscissa(ii.get());
    mNext = (y2 - y1) / (x2 - x1);
    ii.back();

    // Retrocediendo
    ii.back();
    y2 = getOrdinate(ii.get());
    x2 = getAbscissa(ii.get());
    mBack = (y2 - y1) / (x2 - x1);
    ii.next();

    int i = ii.get();
    while(i != indexEnd){
        result.push_back(Vector2(getAbscissa(i), getOrdinate(i)));

        // Avanzando en la iteracion
        if(mNext < mBack)
            ii.next();
        else
            ii.back();
        i = ii.get();
    }

    result.push_back(Vector2(getAbscissa(i), getOrdinate(i)));

    return result;
}

bool Polygon2::domina(Point2 point2) {
    std::list<Vector2> bottomPath = getBottomPath();
    bool first = true;
    Vector2 *fv = nullptr;
    for (auto &vector : bottomPath) {
        if(first) {
            fv = &vector;
            first = false;
            continue;
        }

        Segment2 s = Segment2(*fv, vector);
        if(s.domina(point2))
            return true;

        fv = &vector;
    }
    return false;
}

bool Polygon2::onPolygon(Vector2 pos) {
    return onPolygon(pos.getAbscissa(), pos.getOrdinate());
}

bool Polygon2::onPolygon(float fx, float fy) {
    int j = path.size()-1;
    bool adentro = false;
    long long x = fx * precision;
    long long y = fy * precision;
    for(int i = 0; i < path.size(); i++){
        if((path[i].Y < y and path[j].Y >= y) or (path[j].Y < y and
        path[i].Y >= y))
            if(path[i].X + (y - path[i].Y) / (path[j].Y -
                path[i].Y) * (path[j].X - path[i].X) < x)
                adentro = !adentro;
        j = i;
    }
    return adentro;
}
