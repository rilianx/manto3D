//
// Created by Braulio Lobo on 25-01-20.
//

#ifndef MANTO_TRIANGLE2_H
#define MANTO_TRIANGLE2_H


#include "Segment2.h"

class Triangle2 : public Figure2{

    // Vectores del triangulo
    Vector2 p1 = Vector2(0,0);
    Vector2 p2 = Vector2(1,1);
    Vector2 p3 = Vector2(1,2);

public:
    Triangle2(const Vector2 &p1, const Vector2 &p2, const Vector2 &p3);
    Triangle2(float p1a, float p1o, float p2a, float p2o, float p3a, float p3o);
    Triangle2();

    const Vector2 &getP11() const;
    const Vector2 &getP21() const;
    const Vector2 &getP3() const;

    /**
     * Genera la llave que se utiliza para identifica este punto en el mapa
     * ordenado. Esta corresponde al valor de su abscissa.
     * @return  - Retorna la llave generada.
     */
    virtual float getKey();
    virtual std::string toString();
    virtual std::string toGraphString(int PROJECTION_PLANE);

};


#endif //MANTO_TRIANGLE2_H
