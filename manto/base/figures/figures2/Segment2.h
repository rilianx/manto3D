//
// Created by Braulio Lobo on 11-10-19.
//

#ifndef MANTO_SEGMENT2_H
#define MANTO_SEGMENT2_H


#include <spaces/spaces2/Vector2.h>
#include "Figure2.h"

class Segment2 : public Figure2 {

    // Vectores del segmento
    Vector2 p1 = Vector2(0,0);
    Vector2 p2 = Vector2(1,1);

public:
    Segment2(float ab1, float or1, float ab2, float or2);
    Segment2(Vector2 p1, Vector2 p2);
    Segment2();
    ~Segment2();

    /**
     * Genera la llave que se utiliza para identifica este punto en el mapa
     * ordenado. Esta corresponde al valor de su abscissa.
     * @return  - Retorna la llave generada.
     */
    virtual float getKey();
    virtual std::string toString();
    virtual std::string toGraphString(int PROYECTION_PLANE);
};


#endif //MANTO_SEGMENT2_H
