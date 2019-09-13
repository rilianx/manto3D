//
// Created by Braulio Lobo on 9/6/19.
//

#ifndef MANTO_MANTO_H
#define MANTO_MANTO_H

#include <list>
#include "figures/Figure.h"

using namespace std;

class Manto {

    list<Figure*> lFigures; // Lista de figuras del manto

private:

    /**
     * Intersecta la figura f con todas las figuras del manto. Como resultado:
     *  - Las figuras del manto se fragmentan y sus partes dominadas se
     *    eliminan.
     *  - La figura f se fragmenta, sus conjuntos de fragmentos no dominados
     *    se intersectan.
     * @param f - Figura que se quiere procesar
     * @return  - La fucnion retorna los fragmentos no dominados de f.
     */
    list<Figure*> processFigure(Figure* f);

    /**
     * Comprueba el contenido de ambas listas y retorna una lista con los
     * elementos que se encuentran en las dos listas.
     * @param list1     - Primera lista que se quiere comparar
     * @param list2     - Segunda list aque se quiere comparar
     * @return          - Retorna una lista intersección de ambas entregadas
     */
    list<Figure*> intersect(list<Figure*> list1, list<Figure*> list2);

    /**
     * Intersecta la figura 1 y la figura 2 (en caso de que se pueda). Ambas
     * se fragmentan dependiendo de la intersección y se comprueban los
     * fragmentos que serán dominados y los que no.
     * El tratamiento de los fragmentos generados es el siguiente:
     * - Se genera una lista con los fragmentos de la figura 1 que no son
     *   dominados.
     *
     * @param figure1   - Figura que se quiere fragmentar. Se retornarán los
     *                    fragmetnos de esta figura que no son dominados
     * @param figure2   - Figura que se quiere fragmentar.
     * @return          - Retorna los fragmentos de la figura 1 que no son
     *                    dominados.
     */
    list<Figure*> non_dominated_fragments(Figure* figure1, Figure* figure2);

public:
    ~Manto();

    /**
     * Agrega una figura al manto. Realiza todas las operaciones necesarias
     * para verificar las figuras ya existentes y comprobar si son dominadas.
     */
    void addFigure(Figure* figure);

    /**
     * Imprime todas las figuras que hay en el manto
     */
    void printAllFigures();

};


#endif //MANTO_MANTO_H
