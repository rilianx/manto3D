//
// Created by Braulio Lobo on 9/7/19.
//

#ifndef MANTO_POINT_H
#define MANTO_POINT_H


#include "../space/Vector.h"
#include "Figure.h"

class Point : public Figure{
    Vector position;

public:
    Point(float x, float y, float z);
    Point(Vector vector);
    ~Point();

    float getX() const;
    float getY() const;
    float getZ() const;

    /**
     * Comprueba si el punto actual (this) domina al punto ingresado como
     * parametro.
     * @param point - Punto que se va a comprobar si es dominado por el actual.
     * @return      - Retorna true si es que domina al punto "point"
     */
    bool dominate(Point point) const;

    /**
     * Genera un string con las coordenadas del punto
     * @return  - Retorna un string con las coordenadas del punto
     */
    virtual std::string toString();
};


#endif //MANTO_POINT_H
