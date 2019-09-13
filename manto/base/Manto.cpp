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

    for(auto & figure : lFigures){
        // TODO:
        //  programar esto
        //  lFragments <- Intersect (lFragments, non_dominated_fragments(f,
        //  figure))
        //  F’ <- non_dominated_fragments(figure,f)
        //  eliminar figura "figure" y agregar fragmentos F’ al manto
        lFragments = intersect(lFragments, non_dominated_fragments(f, figure));

        // Actualizando fragmentos no dominados de figure
        list<Figure *> fragmentsFigure = non_dominated_fragments(figure, f);
        // TODO: eliminar figura "figure" del manto
        // TODO: agregar los fragmentos fragmetnsFigure al manto
    }

    return lFragments;
}




