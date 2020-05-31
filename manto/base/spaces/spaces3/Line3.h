//
// Created by Braulio Lobo on 29-05-20.
//

#ifndef MANTO_LINE3_H
#define MANTO_LINE3_H


#include "Vector3.h"
#include "Plane.h"

class Line3 {

private:
    Vector3 director;   // Vector director
    Vector3 point;      // Vector por donde pasa la recta

public:

    Line3(Vector3 director, Vector3 point);

    /**
     * Entrega el punto de interseccion entre la linea y el plano ingresado
     * como parametro
     * @param plane3    - Plano que se va a intersectar con la recta
     * @return          - Retorna un punto de interseccion calculado
     */
    Vector3 intersect(const Plane& plane);

};


#endif //MANTO_LINE3_H
