//
// Created by Braulio Lobo on 24-10-19.
//

#ifndef MANTO_RANGECONTAINER_H
#define MANTO_RANGECONTAINER_H


#include <map>
#include <iostream>
#include "Range.h"

class RangeContainer {

    std::map<int, Range*> rangos; // lInf es la llave

public:

    /**
     * Retorna el rango que contiene al numero ingresado como parametro
     * @param num   - Numero que se quiere buscar en el mapa.
     * @return      - Retorna el rango que contienen al numero ingresado como
     *                parametro.
     */
    Range* loContiene(float num);

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
