//
// Created by Braulio Lobo on 9/18/19.
//

#ifndef MANTO_VECTOR3_H
#define MANTO_VECTOR3_H


#include "../spaces2/Vector2.h"

class Vector3 {

    float x;
    float y;
    float z;

public:

    Vector3(float x, float y, float z);

    /**
     * Obtiene las coordenadas de la proyeccion dependiendo de la constante
     * ingresada como parametro. Estas constantes se encuentran en la clase
     * Figure3.
     * @param PROYECTION_PLANE  - Constante de proyeccion que corresponde al
     *                            plano en el que se quiere obtener la
     *                            proyeccion, por ejemplo:
     *                            Figure3::PROjECTION_XY
     * @return                  - Retorna un vector correspondiente a la
     *                            proyeccion en el plano indicado
     */
    Vector2 getProjection(int PROJECTION_PLANE);

    float getX() const;
    float getY() const;
    float getZ() const;



};


#endif //MANTO_VECTOR3_H
