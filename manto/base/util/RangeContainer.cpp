//
// Created by Braulio Lobo on 24-10-19.
//

#include "RangeContainer.h"

Range *RangeContainer::loContiene(float num) {
    // Si el numero ingresado es menor al menor del mapa ordenado
    if(rangos.empty() || rangos.begin()->first > num) {
        return nullptr;
    }

    // FIXME: hay que comprobar los limites de los rangos para ver si
    //  contiene al numero.

    // Obteniendo el rango que podria contener al numero
    auto iter = rangos.lower_bound(num);
    if(iter->second != nullptr && iter->second->getLInf() == num){
        return iter->second;
    }

    Range* lowerBound = (--iter)->second;

    // Comprobando que el rango obtenido si contiene al numero
    if(lowerBound->contiene(num)) {
        return lowerBound;
    }
    else{
        return nullptr;
    }
}

void RangeContainer::agregarRango(float lInf, float lSup) {
    std::cout << "Agregando rango " << lInf << ", " << lSup << std::endl;

    Range* solapado = loContiene(lInf);

    // Si no esta solapado con un rango menor al nuevo
    if(solapado == nullptr){
        auto nuevoRango = new Range(lInf, lSup);
        rangos.insert({lInf,nuevoRango});
        size++;
    }

        // Si esta solapado con un rango menor al nuevo
    else
        solapado->setLimit(lSup);

    // Si esta solapado con un rango mayor al nuevo
    solapado = loContiene(lSup);
    if(solapado != nullptr && solapado->getLInf() > lInf){
        // Borrando rango solapado del mapa
        rangos.erase(solapado->getLInf());
        size--;

        // Alargando rango menor al limite superior del mayor
        loContiene(lInf)->setLimit(solapado->getLSup());
    }

    while(primerRangoDentro(lInf,lSup) != nullptr){
        rangos.erase(primerRangoDentro(lInf,lSup)->getLInf());
        size--;
    }

    std::cout << "Rango agregado... Resultado: " << std::endl;
    imprimirRangos();
    std::cout << "\n" << std::endl;
}

Range *RangeContainer::primerRangoDentro(float lInf, float lSup) {
    if(size == 0 || rangos.begin()->first > lSup
            || rangos.end()->first < lInf)
        return nullptr;

    Range* lowerBound = (rangos.upper_bound(lInf))->second;
    if(lowerBound->getLSup() <= lSup)
        return lowerBound;
    return nullptr;
}

void RangeContainer::toSegments(std::list<Figure3*> &lFigures, Segment3
sMother){
    for (auto &rango : rangos) {
        Vector3 p1 = sMother.getP(rango.second->getLInf());
        Vector3 p2 = sMother.getP(rango.second->getLSup());
        lFigures.push_back(new Segment3(p1, p2));
    }
}
