//
// Created by Braulio Lobo on 9/10/19.
//

#ifndef MANTO_PLANE_H
#define MANTO_PLANE_H


#include "Vector.h"
#include "../figures/Point.h"

class Plane {
    Vector vNormal; // Vector normal
    Point point;    // Punto del plano

    // Variables de la ecuacion del plano general
    float a;
    float b;
    float c;
    float d;

public:
    Plane(Vector vDirector1, Vector vDirector2, Point p);
    Plane(Vector vNormal, Point p);
    Plane(Point p1, Point p2, Point p3);

    Vector getNormal();

    // ToDo: Terminar de escribir las funciones del plano (Intersecciones y mas)
    // TODO: funciones para saber si domina o es dominado, ademas de fracturas

private:
    void updateGeneralEquation();
};


#endif //MANTO_PLANE_H
