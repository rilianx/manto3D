//
// Created by Braulio Lobo on 26-01-20.
//

#ifndef MANTO_LINE2_H
#define MANTO_LINE2_H


#include <figures/figures2/Segment2.h>
#include "Vector2.h"

class Line2 {

private:
    Vector2 d;  // Vector director
    Vector2 p;  // Punto que pasa por la recta

public:
    Line2();
    Line2(Vector2 p1, Vector2 p2);
    Line2(Vector2 director, Vector2 point, bool def);

    /**
     * Entrega el punto de interseccion entre el segmento y la linea
     * ingresada como parametro
     * @param segment   - Segmento con el que se quiere intersectar la linea
     * @return          - Retorna el punto de interseccion y null si no hubo
     *                    interseccion
     */
    Vector2* intersect(Segment2 segment);

    /**
     * Entrega el punto de interseccion entre el segmento generado por los
     * dos puntos ingresados como parametro y la linea
     * @param segment   - Segmento con el que se quiere intersectar la linea
     * @return          - Retorna el punto de interseccion y null si no hubo
     *                    interseccion
     */
    Vector2* intersect(Vector2 p1, Vector2 p2);

    /**
     * Evalua la funcion de la linea (recta) en el valor x entregado como
     * parametro
     * @param x     - Valor que se va evaluar
     */
     float evalue(float x);
};


#endif //MANTO_LINE2_H
