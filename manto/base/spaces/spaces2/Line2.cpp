//
// Created by Braulio Lobo on 26-01-20.
//

#include "Line2.h"

Line2::Line2(Vector2 p1, Vector2 p2) {
    this->d = {p2.getAbscissa() - p1.getAbscissa(),
               p2.getOrdinate() - p1.getOrdinate()};
    this->p = p1;
}

Vector2 *Line2::intersect(Segment2 segment) {
    return intersect(segment.getP1(), segment.getP2());
}

Vector2 *Line2::intersect(Vector2 p1, Vector2 p2) {
    // Ordenando los puntos usando la absisa
    Vector2 pp1 = (p1.getAbscissa() < p2.getAbscissa()) ? p1 : p2;
    Vector2 pp2 = (pp1.getAbscissa() == p1.getAbscissa()) ? p2 : p1;

    // Vector director del segmento
    Vector2 d2 =  {p2.getAbscissa() - p1.getAbscissa(),
                   p2.getOrdinate() - p1.getOrdinate()};
    Vector2 c = {p1.getAbscissa() - p.getAbscissa(),
                 p1.getOrdinate() - p.getOrdinate()};

    // Determinante de la ecuacion
    float det = - this->d.getAbscissa() * d2.getOrdinate() + d2.getAbscissa()
            * this->d.getOrdinate();

    // Lambda de la linea que genera el punto
    float lambda = (c.getAbscissa() * - d2.getOrdinate() + d2.getAbscissa() *
            c.getOrdinate()) / det;

    Vector2* pIntersect = new Vector2(
            p.getAbscissa() + lambda * d.getAbscissa(),
            p.getOrdinate() + lambda * d.getOrdinate());

    // Comprobando si el punto de interseccion está dentro del segmento
    // ingresado
    if(pIntersect->getAbscissa() <= pp2.getAbscissa() &&
        pIntersect->getAbscissa() >= pp1.getAbscissa()) {
        Vector2 pp1 = (p1.getOrdinate() < p2.getOrdinate()) ? p1 : p2;
        Vector2 pp2 = (pp1.getOrdinate() == p1.getOrdinate()) ? p2 : p1;
        if (pIntersect->getOrdinate() <= pp2.getOrdinate() &&
            pIntersect->getOrdinate() >= pp1.getOrdinate())
            return pIntersect;
    }
    return nullptr;
}
