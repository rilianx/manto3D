//
// Created by Braulio Lobo on 9/6/19.
//

#ifndef MANTO_MANTO_H
#define MANTO_MANTO_H

#include <list>
#include "figures/Figure.h"

using namespace std;

class Manto {

    list<Figure> lFigures; // Lista de figuras

public:
    void addFigura(const Figure& figure);
    void printAllFigures();
};


#endif //MANTO_MANTO_H
