//
// Created by Braulio Lobo on 9/7/19.
//

#ifndef MANTO_FIGURE_H
#define MANTO_FIGURE_H


#include <string>
#include <list>

class Figure {

public:
    ~Figure();

    /**
     * Genera un string caracteristico de la figura
     * @return  - Retorna el string generado
     */
    virtual std::string toString(){
        return "Figure";
    }
};


#endif //MANTO_FIGURE_H
