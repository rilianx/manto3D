//
// Created by Braulio Lobo on 20-03-20.
//

#ifndef MANTO_INTERSECTOR_H
#define MANTO_INTERSECTOR_H

#include "figures/figures3/Figure3.h"
#include "figures/figures2/Polygon2.h"
#include "figures/figures3/Polygon3.h"

using namespace ClipperLib;

class Intersector {
    Polygon3* polygon3;
    Paths resultado;
    Clipper* cplr;

public:
    Intersector(Polygon3* polygon3);
    ~Intersector();

    /**
     * Agrega un nuevo poligono y lo intersecta a la solucion de todos los
     * poligonos que se han agregado anteriormente
     * @param polygon2          - Poligono que se quiere agregar. Este tiene
     *                            que ser la proyeccion en el plano XY del
     *                            poligono real.
     * @param PROJECTION_PLANE  - Plano al que pertenece el poligono que se
     *                            esta agregando.
     */
    void add(Polygon2* polygon2);

    /**
     * Obtiene la solucion de todos los poligonos agregados y unidos.
     * @return  - Retorna una lista de poligonos unidos en el plano del
     *            polygon3 con que se inicializo el Glue.
     */
    std::list<Figure3*> getResult();
};


#endif //MANTO_INTERSECTOR_H
