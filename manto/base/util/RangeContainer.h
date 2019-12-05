//
// Created by Braulio Lobo on 24-10-19.
//

#ifndef MANTO_RANGECONTAINER_H
#define MANTO_RANGECONTAINER_H


#include <map>
#include <iostream>
#include <figures/figures3/Figure3.h>
#include <figures/figures3/Segment3.h>
#include "Range.h"

class RangeContainer {

    std::map<float, Range*> rangos; // lInf es la llave
    int size = 0;

public:

    /**
     * Retorna el rango que contiene al numero ingresado como parametro
     * @param num   - Numero que se quiere buscar en el mapa.
     * @return      - Retorna el rango que contienen al numero ingresado como
     *                parametro.
     */
    Range* loContiene(float num);

    /**
     * Busca el primer rango dentro de los limites ingresados como parametro
     * œparam lInf  - Limite inferior del intervalo donde se quiere buscar el
     *                rango.
     * @param lSup  - Limite superior del intervalo donde se quiere buscar el
     *                rango.
     * @return      - Retorna el primer rango contenido entre los limites
     *                ingresados como parametro.
     */
    Range* primerRangoDentro(float lInf, float lSup);

    /**
     * Agrega el rango ingresado como parametro al contenedor de rangos
     * @param lInf  - Limite inferior del rango que se quiere agregar al rango.
     * @param lSup  - Limite superior del rango que se quiere agregar al rango.
     */
    void agregarRango(float lInf, float lSup);

    void imprimirRangos(){
        for (auto &rango : rangos) {
            std::cout << rango.second->getLInf() << ", "<<
                         rango.second->getLSup() << std::endl;
        }
    }

    /**
     * Crea sub segmentos dentro del segmento madre ingresado como parametro
     * y los agrega a la lista de figuras. Estos sub segmentos son creados en
     * base a los valores de los rangos contenidos en este contenedor.
     * @param lFigures  - Lista de figuras que se llenará con los segmentos
     *                    creados.
     * @param sMother   - Segmento que contiene a los sub segmentos que se
     *                    van a crear.
     */
    void toSegments(std::list<Figure3*> &lFigures, Segment3 sMother);
};


#endif //MANTO_RANGECONTAINER_H
