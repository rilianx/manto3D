//
// Created by Braulio Lobo on 10-10-19.
//

#ifndef MANTO_SEGMENT3_H
#define MANTO_SEGMENT3_H


#include <spaces/spaces3/Vector3.h>
#include <figures/figures2/Segment2.h>
#include "Figure3.h"

class Segment3 : public Figure3{

    Vector3 p1 = Vector3(0,0,0);
    Vector3 p2 = Vector3(1,1,1);
    Segment2 projections[3];

private:
    /**
     * Genera las proyecciones del segmento y las guarda en el arreglo de
     * proyecciones
     */
    void generateProjections();

public:
    Segment3(float p1x, float p1y, float p1z, float p2x, float p2y, float p2z);
    Segment3(Vector3 p1, Vector3 p2);
    ~Segment3();

    float getMenorX();
    float getMenorY();
    float getMenorZ();
    float getMaxX();
    float getMaxY();
    float getMaxZ();

    bool equal(Segment3* segment);

    /**
     * Obtiene las proyecciones de la figura
     * @param PROJECTION_PLANE  - Indice constante del plano donde se quiere
     *                            obtener la proyeccion (Por ejemplo:
     *                            PROJECTION_XY)
     * @return                  - Retorna la proyeccion de la punto en el
     *                            plano indicado en el parametro
     */
    virtual Segment2* getProjection(int PROJECTION_PLANE);

    virtual std::string toString();
    virtual std::string toGraphString();

};

#endif //MANTO_SEGMENT3_H