//
// Created by Braulio Lobo on 9/6/19.
//

#include <iostream>
#include "Manto.h"
#include "figures/Point.h"

void Manto::addFigure(Figure* figure) {
    // Creando lista de fragmentos y procesando insercion de la figura
    list<Figure*> lFragmentos = processFigure(figure);

    // Agragando fragmentos no dominados del parametro figure
    for(auto fragment : lFragmentos)
        lFigures.push_back(fragment);
}

void printFigure(Figure* f){
    std::cout<<f->toString()<<std::endl;
}

void Manto::printAllFigures() {
    // Seteando la lista en el inicio
    lFigures.begin();

    // Iterando las figuras e imprimiendolas
    for(auto & figure : lFigures){
        printFigure(figure);
    }
}

Manto::~Manto() {
    std::cout << "Eliminando manto" << std::endl;

    // Iterando las figuras y eliminandolas
    for(auto figure : lFigures){
        Point * p = dynamic_cast<Point*>(figure);
        if(p != NULL)
            delete p;
        else
            delete figure;
    }

    std::cout << "Manto eliminado" << std::endl;
}

list<Figure *> Manto::processFigure(Figure *f) {
    list<Figure *> lFragments;  // Fragmentos no dominados de la figura f
    lFragments.push_back(f);    // Figura completa como fragmento no dominado

    // Iterador
    list<Figure *>::iterator itr = lFigures.begin();

    for(auto & figure : lFigures){
        // Intersectando las listas de fragmentos
        lFragments = intersect(lFragments, non_dominated_fragments(f, figure));

        // Actualizando fragmentos no dominados de figure
        list<Figure *> fragmentsFigure = non_dominated_fragments(figure, f);

        // Si se generaron fragmentos se elimina la figura del manto y se
        // agregan sus fragmentos no dominados
        if(fragmentsFigure.size() > 1){
            // FIXME:
            //   - sacarlo y ponerlo
            //   - Colocar los fragmentos y figuras en una lista temporal e ir
            //   borrando esta, luego eliminar esta lista y agregar los
            //   elementos de la nueva (La temporal.


            // Eliminando figure del manto
            lFigures.erase(itr);

            // Agregando los fragmentos de figure al manto
            for(auto & fragment : fragmentsFigure)
                lFigures.push_back(fragment);
        }
        else{ // Avanzando en el iterador
            itr++;
        }

    }

    return lFragments;
}




