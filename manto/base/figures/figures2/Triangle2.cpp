//
// Created by Braulio Lobo on 25-01-20.
//

#include <spaces/spaces2/Line2.h>
#include <sstream>
#include <iostream>
#include "Triangle2.h"



const Vector2 &Triangle2::getP1() const {
    return p1;
}

const Vector2 &Triangle2::getP2() const {
    return p2;
}

const Vector2 &Triangle2::getP3() const {
    return p3;
}

Triangle2::Triangle2(const Vector2 &p1, const Vector2 &p2, const Vector2 &p3)
        : p1(p1), p2(p2), p3(p3) {}

Triangle2::Triangle2(float p1a, float p1o, float p2a, float p2o, float p3a,
                     float p3o) {

}

float Triangle2::getKey() {
    return 0;
}

std::string Triangle2::toString() {
    std::ostringstream ss;
    ss << "T(" << p1.getAbscissa() << ", " << p1.getOrdinate() << ")";
    ss << "->(" << p2.getAbscissa() << ", " << p2.getOrdinate() << ")";
    ss << "->(" << p3.getAbscissa() << ", " << p3.getOrdinate() << ")";
    std::string s(ss.str());
    return s;
}

std::string Triangle2::toGraphString(int PROJECTION_PLANE) {
    return std::string();
}

Triangle2::Triangle2() {}

Triangle2** Triangle2::split(Vector2 pl1, Vector2 pl2) {
    // Generando la linea que pasa por los puntos pl1 y pl2
    Line2 line = {pl1, pl2};

    std::list<Vector2*> puntos;   // Puntos de interseccion

    Vector2* polygon = new Vector2[5];  // Contenedor de path del poligono
    int size_polygon = 0;               // Numero de path del poligono
    int index_init = -1;
    int index_end = -1;

    Vector2* pi = line.intersect(this->p1, this->p2);
    polygon[size_polygon++] = this->p1;
    if(pi != nullptr){
        index_init = size_polygon;
        polygon[size_polygon++] = *pi;
    }
    polygon[size_polygon++] = this->p2;

    pi = line.intersect(this->p2, this->p3);
    if(pi != nullptr){
        if(index_init == -1)
            index_init = size_polygon;
        else
            index_end = size_polygon;
        polygon[size_polygon++] = *pi;
    }
    polygon[size_polygon++] = this->p3;

    pi = line.intersect(this->p3, this->p1);
    if(pi != nullptr){
        if(index_init == -1)
            index_init = size_polygon;
        else
            index_end = size_polygon;
        polygon[size_polygon++] = *pi;
    }

    if(size_polygon < 5)
        return nullptr;

    // Generando triangulacion
    Triangle2* t1;
    Triangle2* t2;
    Triangle2* t3;
    if((index_init + 2)%size_polygon == index_end){
        // El camino mas corto del corte es sumando
        int index = index_init;
        t1 = new Triangle2(polygon[index++],
                polygon[(index++)%size_polygon],
                polygon[(index++)%size_polygon]);
        index = index_init;
        t2 = new Triangle2(polygon[index--],
                polygon[(index-- + size_polygon) % size_polygon],
                polygon[(index + size_polygon) % size_polygon]);
        t3 = new Triangle2(polygon[(index-- + size_polygon) %
                                              size_polygon],
                                      polygon[(index + size_polygon) % size_polygon],
                                      polygon[index_init]);
    }
    else{
        // El camino mas corto del corte es restando
        int index = index_init;
        t1 = new Triangle2(polygon[index--],
                           polygon[(index-- + size_polygon) % size_polygon],
                           polygon[(index-- + size_polygon) % size_polygon]);
        index = index_init;
        t2 = new Triangle2(polygon[index++],
                           polygon[(index++)%size_polygon],
                           polygon[(index)%size_polygon]);
        t3 = new Triangle2(polygon[index++],
                           polygon[index%size_polygon],
                           polygon[index_init]);
    }

    Triangle2** triangles = new Triangle2*[3];
    triangles[0] = t1;
    triangles[1] = t2;
    triangles[2] = t3;

    return triangles;
}

void Triangle2::fragmentedBy(Point2 *p, std::list<Figure2 *> &fragments) {
    // TODO (En proceso): fragmentacion de triangulos por puntos
    // Obteniendo
    Vector2 v = {p->getAbscissa(), p->getOrdinate()};
    Vector2 vx = {p->getAbscissa()+100, p->getOrdinate()};
    Vector2 vy = {p->getAbscissa(), p->getOrdinate()+100};

    // Generando fragmentos
    Triangle2** spl1 = split(v, vx);

    if(spl1 != nullptr){
        for (int i = 0; i < 3; ++i) {
            Triangle2** spl2 = spl1[i]->split(v, vy);
            if(spl2 != nullptr) {
                for (int j = 0; j < 3; ++j)
                    if (!p->domina(*spl2[j]))
                        fragments.push_front(spl2[j]);
            }
            else{
                if(!p->domina(*spl1[i]))
                    fragments.push_front(spl1[i]);
            }
        }
    }
    else{
        spl1 = split(v, vy);
        if(spl1 != nullptr)
            for (int i = 0; i < 3; ++i)
                if(!p->domina(*spl1[i]))
                    fragments.push_front(spl1[i]);
    }

}

void Triangle2::fragmentedBy(Segment2 *s, std::list<Figure2 *> &fragments) {
    // TODO: fragmentacion de triangulos por segmentos
}

void Triangle2::fragmentedBy(Triangle2 *t, std::list<Figure2 *> &fragments) {
    // TODO: fragmentacion de triangulos por triangulos
}

bool Triangle2::domina(Point2 p) {
    // TODO: triangulo domina a punto
    return false;
}


