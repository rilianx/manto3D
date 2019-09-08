//
// Created by Braulio Lobo on 9/6/19.
//

#include <iostream>
#include "Manto.h"

void Manto::addFigura(const Figure& figure) {
    lFigures.push_back(figure);
}

void printFigure(Figure f){
    std::cout<<f.toString()<<std::endl;
}

void Manto::printAllFigures() {
    // Seteando la lista en el inicio
    lFigures.begin();

    // Iterando las figuras e imprimiendolas
    for(auto & figure : lFigures){
        printFigure(figure);
    }
}



