//
// Created by Braulio Lobo on 24-10-19.
//

#ifndef MANTO_RANGECONTAINER_H
#define MANTO_RANGECONTAINER_H


#include <map>
#include <iostream>
#include "Range.h"

class RangeContainer {

    std::map<float, Range*> rangos; // lInf es la llave

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
};


#endif //MANTO_RANGECONTAINER_H
