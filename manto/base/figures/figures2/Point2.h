//
// Created by Braulio Lobo on 9/19/19.
//

#ifndef MANTO_POINT2_H
#define MANTO_POINT2_H


#include "../../spaces/spaces2/Vector2.h"
#include "Figure2.h"

class Point2 : public Figure2{

    Vector2 position = Vector2(0, 0);

public:
    Point2(float abscissa, float ordinate);
    Point2(Vector2 position);
    Point2();
    ~Point2();

    float getAbscissa() const;
    float getOrdinate() const;

    const Vector2 &getPosition() const;

    /**
     * Genera la llave que se utiliza para identifica este punto en el mapa
     * ordenado. Esta corresponde al valor de su abscissa.
     * @return  - Retorna la llave generada.
     */
    virtual float getKey();
    virtual std::string toString();
    virtual std::string toGraphString(int PROYECTION_PLANE);

};


#endif //MANTO_POINT2_H
