//
// Created by Braulio Lobo on 9/18/19.
//

#ifndef MANTO_FIGURE3_H
#define MANTO_FIGURE3_H


#include <string>
#include "Figure2.h"

class Figure3 {

public:

    // Constantes para los indices de proyecciones
    static const int PROJECTION_XY = 0;
    static const int PROJECTION_XZ = 1;
    static const int PROJECTION_YZ = 2;

    // Constantes para identificar que tipo de instancia es
    static const int POINT_INSTANCE = 0;
    static const int SEGMENT_INSTANCE = 1;

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

    /**
     * Comprueba si la figura actual (this) es dominada por la figura
     * ingresada por parametro.
     * @param figure3   - Figura que podria (o no) dominar a esta figura (this).
     * @return          - Retorna True si figure3 domina a esta figura (this) y
     *                    Retorna falso en el caso contrario.
     */
    virtual bool isDominated(Figure3 *figure3) = 0;

    /**
     * Obtiene la instancia de la figura. Esto se hace así para evitar hacer
     * casteos dinámicos demasiadas veces, de esta forma se reduce el tiempo
     * de ejecución.
     * @return  - Retorna un entero correspondiente a la instancia de la
     *            figura. Por ejemplo, POINT_INSTANCE, SEGMENT_INSTANCE, etc.
     */
    virtual int getInstance() = 0;
};


#endif //MANTO_FIGURE3_H
