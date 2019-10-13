//
// Created by Braulio Lobo on 9/18/19.
//

#ifndef MANTO_VECTOR2_H
#define MANTO_VECTOR2_H


class Vector2 {

    // El sistema de coordenadas para planos es: (abscissa, ordinate)
private:
    float abscissa;
    float ordinate;

public:
    Vector2(float abscissa, float ordinate);

    float getAbscissa() const;
    float getOrdinate() const;
};


#endif //MANTO_VECTOR2_H
