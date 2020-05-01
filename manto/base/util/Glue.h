//
// Created by Braulio Lobo on 07-03-20.
//

#ifndef MANTO_GLUE_H
#define MANTO_GLUE_H


#include "figures/figures3/Figure3.h"
#include "figures/figures2/Polygon2.h"
#include "figures/figures3/Polygon3.h"

using namespace ClipperLib;

class Glue {
    Polygon3* polygon3;
    int unionPlane = Figure3::PROJECTION_XY;
    Paths resultado;
    Clipper* cplr;
    int agregados = 0;

public:
    Glue(Polygon3* polygon3);
    ~Glue();

    /**
     * Agrega un nuevo poligono y lo une a la solucion de todos los poligonos
     * que se han agregado anteriormente
     * @param polygon2          - Poligono que se quiere agregar
     * @param PROJECTION_PLANE  - Plano al que pertenece el poligono que se
     *                            esta agregando.
     */
    void add(Polygon2* polygon2, int PROJECTION_PLANE);

    /**
     * Obtiene la solucion de todos los poligonos agregados y unidos.
     * @return  - Retorna una lista de poligonos unidos en el plano del
     *            polygon3 con que se inicializo el Glue.
     */
    std::list<Figure3*> getResult();
};


#endif //MANTO_GLUE_H
