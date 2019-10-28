//
// Created by Braulio Lobo on 24-10-19.
//

#include "RangeContainer.h"

Range *RangeContainer::loContiene(float num) {
    std::cout << "[Lo contiene]" << std::endl;
    // Si el numero ingresado es menor al menor del mapa ordenado
    if(rangos.empty() || rangos.begin()->first > num) {
        if(rangos.empty())
            std::cout << "  Contenedor de rangos vacío" << std::endl;
        else
            std::cout << "  No hay lowerBound del numero " << num <<
                      std::endl;
        return nullptr;
    }

    // Obteniendo el rango que podria contener al numero
    Range* lowerBound = rangos.upper_bound(num)->second;
    std::cout << "  LowerBound de " << num << " es "
              << rangos.lower_bound(num)->first << std::endl;

    // Comprobando que el rango obtenido si contiene al numero
    if(lowerBound->contiene(num)) {
        std::cout << "  Rango encontrado" << std::endl;
        return lowerBound;
    }
    else{
        std::cout << "  " << lowerBound->getLInf() << ", " <<
                  lowerBound->getLSup() << " no contiene a " << num << std::endl;
        std::cout << "  Rango no encontrado" << std::endl;
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
    if(solapado != nullptr && solapado->getLInf() != lInf){
        std::cout << "Borrando solapamiento superior" << std::endl;
        // Borrando rango solapado del mapa
        rangos.erase(solapado->getLInf());

        // Alargando rango menor al limite superior del mayor
        loContiene(lInf)->setLimit(solapado->getLSup());
    }
}
