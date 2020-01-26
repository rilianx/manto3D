//
// Created by Braulio Lobo on 25-01-20.
//

#ifndef MANTO_TRIANGLE3_H
#define MANTO_TRIANGLE3_H


#include <spaces/spaces3/Vector3.h>
#include <figures/figures2/Triangle2.h>
#include "Figure3.h"

class Triangle3 : public Figure3{

    Vector3 p1 = Vector3(0,0,0);
    Vector3 p2 = Vector3(0,0,0);
    Vector3 p3 = Vector3(0,0,0);
    Triangle2 projections[3];

private:
    /**
     * Genera las proyecciones del segmento y las guarda en el arreglo de
     * proyecciones
     */
    void generateProjections();

public:

    Triangle3(float p1x, float p1y, float p1z,
              float p2x, float p2y, float p2z,
              float p3x, float p3y, float p3z);
    Triangle3(Vector3 p1, Vector3 p2, Vector3 p3);


    /**
     * Obtiene las proyecciones de la figura
     * @param PROJECTION_PLANE  - Indice constante del plano donde se quiere
     *                            obtener la proyeccion (Por ejemplo:
     *                            PROJECTION_XY)
     * @return                  - Retorna la proyeccion de la punto en el
     *                            plano indicado en el parametro
     */
    virtual Triangle2* getProjection(int PROJECTION_PLANE);
    virtual std::string toString();
    virtual std::string toGraphString();

    virtual int getInstance();
    virtual bool equal(Figure3 *figure3);
    virtual bool isDominated(Figure3* figure);

};


#endif //MANTO_TRIANGLE3_H
