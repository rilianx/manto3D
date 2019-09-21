//
// Created by Braulio Lobo on 9/6/19.
//

#ifndef MANTO_MANTO_H
#define MANTO_MANTO_H

#include <list>
#include <map>
#include "figures/figures3/Figure3.h"
#include "figures/figures2/Figure2.h"

using namespace std;

class Manto {

    // Lista de figuras en 3 dimensiones
    list<Figure3*> lFigure3;

    // Mapas ordenados de proyecciones. Las llaves de estos mapas
    // corresponden a las coordenada abscissas menores de cada figura.
    std::map<float,Figure2*> mapFigureXY; // Proyecciones en el plano XY
    std::map<float,Figure2*> mapFigureXZ; // Proyecciones en el plano XZ
    std::map<float,Figure2*> mapFigureYZ; // Proyecciones en el plano YZ
    // FIXME: hacer listas dentro de los mapas, para así permitir repeticiones

public:
    ~Manto();

    /**
     * Agrega una figura al manto. Procesa esta y las demas figuras del manto
     * para tener el resultado esperado.
     * Este metodo genera las proyecciones y las agrega al mapa ordenado.
     * @param figure    - Figura que se quiere agregar al manto
     */
    void addFigure(Figure3* figure);

    /**
     * Imprime todas las figuras de tres dimensiones
     */
    void printAllFigures3();

    /**
     * Imprime todas las figuras de tres dimensiones con el formato par ase
     * graficadas
     */
    void printAllGraphFigures3();

    /*+
     * Imprime todas las figuras en dos dimensiones que se encuentran en el
     * plano que se indica en el parametro. Es decir, imprime todas las
     * proyecciones sobre el plano
     * @param PROJECTION_PLANE  - Indice del plano donde se encuentran las
     *                            figuras.
     */
    void printAllFigures2(int PROJECTION_PLANE);

    /**
     * Guarda la instancia actual. Genera cuatro archivos:
     *  1. "Figures.txt": Archivo que contiene las figuras en 3 dimensiones.
     *  2. "pxy.txt": Archivo que contiene las figuras proyectadas en el
     *                plano xy.
     *  3. "pxz.txt": Archivo que contiene las figuras proyectadas en el
     *                plano xz.
     *  4. "pyz.txt": Archivo que contiene las figuras proyectadas en el
     *                plano yz.
     * @param path  - Ruta donde se guardará el archivo
     */
    void saveInstance(std::string path);
};


#endif //MANTO_MANTO_H
