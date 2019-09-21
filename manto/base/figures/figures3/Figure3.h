//
// Created by Braulio Lobo on 9/18/19.
//

#ifndef MANTO_FIGURE3_H
#define MANTO_FIGURE3_H


#include <string>
#include "../figures2/Figure2.h"

class Figure3 {

public:

    // Constantes para los indices de proyecciones
    static const int PROJECTION_XY = 0;
    static const int PROJECTION_XZ = 1;
    static const int PROJECTION_YZ = 2;

    /**
     * Obtiene las proyecciones de la figura.
     * @param PROJECTION_PLANE  - Indice constante del plano donde se quiere
     *                            obtener la proyeccion (Por ejemplo:
     *                            PROJECTION_XY)
     * @return                  - Retorna la proyeccion de la figura en el
     *                            plano indicado en el parametro
     */
    virtual Figure2* getProjection(int PROJECTION_PLANE) = 0;
    virtual std::string toString() = 0;
    virtual std::string toGraphString() = 0;
};


#endif //MANTO_FIGURE3_H
