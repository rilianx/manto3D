//
// Created by Braulio Lobo on 9/19/19.
//

#ifndef MANTO_POINT3_H
#define MANTO_POINT3_H


#include "../../spaces/spaces3/Vector3.h"
#include "../figures2/Point2.h"
#include "Figure3.h"

class Point3 : public Figure3{

    Vector3 position = Vector3(0,0,0);
    Point2 projections[3];

private:
    /**
     * Genera las proyecciones del punto y las guarda en el arreglo de
     * proyecciones
     */
    void generateProjections();

public:
    Point3(float x, float y, float z);
    Point3(Vector3 position);
    ~Point3();

    float getX() const;
    float getY() const;
    float getZ() const;

    /**
     * Obtiene las proyecciones de la figura.
     * @param PROJECTION_PLANE  - Indice constante del plano donde se quiere
     *                            obtener la proyeccion (Por ejemplo:
     *                            PROJECTION_XY)
     * @return                  - Retorna la proyeccion de la punto en el
     *                            plano indicado en el parametro
     */
    virtual Point2* getProjection(int PROJECTION_PLANE);

    virtual std::string toString();
    virtual std::string toGraphString();
};


#endif //MANTO_POINT3_H
