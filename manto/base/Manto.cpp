//
// Created by Braulio Lobo on 9/6/19.
//

#include <iostream>
#include "Manto.h"
#include "figures/Point.h"

void Manto::addFigura(Figure* figure) {
    lFigures.push_back(figure);
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




