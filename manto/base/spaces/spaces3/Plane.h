//
// Created by Braulio Lobo on 29-05-20.
//

#ifndef MANTO_PLANE_H
#define MANTO_PLANE_H


#include "Vector3.h"
#include "Line3.h"

class Plane {

private:
    // Vectores directores
    Vector3 vd1;
    Vector3 vd2;

    // Punto por donde pasa el plano
    Vector3 point;

    // Normal del plano
    Vector3 normal;

    // Valores de la ecuacion general del plano
    float a;
    float b;
    float c;
    float d;

public:

    Plane(const Vector3& p1, const Vector3& p2, const Vector3& p3);

    /**
     * Obtiene el punto mas cercano entre este plano y las corrdenadas del
     * punto ingresado como parametro
     * @param point     - Coordenadas mas cercana al punto que se va a obtener
     * @return          - Obtiene el punto mas cercano al "point" contenido
     *                    en el plano.
     */
    Vector3 getClosestPointTo(Vector3 point);

    /**
     * Interceptar ambos planos. El resultado de este es una linea
     * @param plane     - Plano que se quiere interceptar con este
     * @return          - Retorna una linea resultante
     */
    Line3* intersect(Plane plane);

    const Vector3 &getVd1() const;

    const Vector3 &getVd2() const;

    const Vector3 &getPoint() const;

    const Vector3 &getNormal() const;

    float getA() const;

    float getB() const;

    float getC() const;

    float getD() const;
};


#endif //MANTO_PLANE_H
