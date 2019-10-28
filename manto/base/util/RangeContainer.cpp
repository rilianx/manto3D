//
// Created by Braulio Lobo on 24-10-19.
//

#include "RangeContainer.h"

Range *RangeContainer::loContiene(float num) {
    // Si el numero ingresado es menor al menor del mapa ordenado
    if(rangos.empty() || rangos.begin()->first > num) {
        return nullptr;
    }

    // Obteniendo el rango que podria contener al numero
    Range* lowerBound = (--rangos.lower_bound(num))->second;

    // Comprobando que el rango obtenido si contiene al numero
    if(lowerBound->contiene(num)) {
        return lowerBound;
    }
    else{
        return nullptr;
    }
}

void RangeContainer::agregarRango(float lInf, float lSup) {
    Range* solapado = loContiene(lInf);

    // Si no esta solapado con un rango menor al nuevo
    if(solapado == nullptr){
        auto nuevoRango = new Range(lInf, lSup);
        rangos.insert({lInf,nuevoRango});
    }

        // Si esta solapado con un rango menor al nuevo
    else
        solapado->setLimit(lSup);

    // Si esta solapado con un rango mayor al nuevo
    solapado = loContiene(lSup);
    if(solapado != nullptr && solapado->getLInf() > lInf){
        // Borrando rango solapado del mapa
        rangos.erase(solapado->getLInf());

        // Alargando rango menor al limite superior del mayor
        loContiene(lInf)->setLimit(solapado->getLSup());
    }

    while(primerRangoDentro(lInf,lSup) != nullptr){
        rangos.erase(primerRangoDentro(lInf,lSup)->getLInf());
    }
}

Range *RangeContainer::primerRangoDentro(float lInf, float lSup) {
    if(rangos.empty() || rangos.begin()->first > lSup
            || rangos.end()->first < lInf)
        return nullptr;

    Range* lowerBound = (rangos.upper_bound(lInf))->second;
    if(lowerBound->getLSup() < lSup)
        return lowerBound;
    return nullptr;
}
