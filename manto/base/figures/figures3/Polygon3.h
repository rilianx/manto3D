//
// Created by Braulio Lobo on 25-02-20.
//

#ifndef MANTO_POLYGON3_H
#define MANTO_POLYGON3_H

#include <spaces/spaces3/Vector3.h>
#include "figures/figures2/Polygon2.h"
#include "Figure3.h"


class Polygon3 : public Figure3{

    int nVectors = 0;
    Vector3* vectors;
    Polygon2 projections[3];

private:
    /**
     * Genera las proyecciones del segmento y las guarda en el arreglo de
     * proyecciones
     */
    void generateProjections();

public:

    Polygon3(Vector3* vectors, int nVectors);
    Polygon3(std::list<Vector3> vectorList, int nVectors);
    ~Polygon3();

    /**
     * Obtiene las proyecciones de la figura
     * @param PROJECTION_PLANE  - Indice constante del plano donde se quiere
     *                            obtener la proyeccion (Por ejemplo:
     *                            PROJECTION_XY)
     * @return                  - Retorna la proyeccion de la punto en el
     *                            plano indicado en el parametro
     */
    virtual Polygon2* getProjection(int PROJECTION_PLANE);
    virtual std::string toString();
    virtual std::string toGraphString();

    virtual int getInstance();
    virtual bool equal(Figure3 *figure3);
    virtual bool isDominated(Figure3* figure);

    Vector3 *getVectors() const;
};


#endif //MANTO_POLYGON3_H
