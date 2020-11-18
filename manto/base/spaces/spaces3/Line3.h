//
// Created by Braulio Lobo on 29-05-20.
//

#ifndef MANTO_LINE3_H
#define MANTO_LINE3_H


#include <spaces/spaces2/Line2.h>
#include "Vector3.h"

class Plane;

class Line3 {

    Line2 projections[3];

private:
    Vector3 director;   // Vector director
    Vector3 point;      // Vector por donde pasa la recta

    /**
     * Genera las proyecciones de la linea y las guarda en el arreglo de
     * proyecciones
     */
    void generateProjections();

public:

    Line3(Vector3 director, Vector3 point);

    /**
     * Entrega el punto de interseccion entre la linea y el plano ingresado
     * como parametro
     * @param plane3    - Plano que se va a intersectar con la recta
     * @return          - Retorna un punto de interseccion calculado
     */
    Vector3 intersect(const Plane& plane);

    Line2 *getProjection(const int i);
};


#endif //MANTO_LINE3_H
