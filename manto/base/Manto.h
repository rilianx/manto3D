//
// Created by Braulio Lobo on 9/6/19.
//

#ifndef MANTO_MANTO_H
#define MANTO_MANTO_H

#include <list>
#include <map>
#include <unordered_set>
#include "figures/figures3/Figure3.h"
#include "figures/figures2/Figure2.h"

using namespace std;

class Manto {

    // Lista de figuras en 3 dimensiones
    std::unordered_set<Figure3*> lFigure3;
    list<Figure3*> lFigure3Dominated; // Lista de figuras dominadas
    list<Figure2*> lFigure2Dominated; // Lista de proyecciones dominadas

    // Mapas ordenados de proyecciones. Las llaves de estos mapas
    // corresponden a las coordenada abscissas menores de cada figura.
    std::map<float,Figure2*> mapFigureXY; // Proyecciones en el plano XY
    std::map<float,Figure2*> mapFigureXZ; // Proyecciones en el plano XZ
    std::map<float,Figure2*> mapFigureYZ; // Proyecciones en el plano YZ
    // FIXME: utilizar Vector2* en vez de float de los mapas, para así permitir
    //        repeticiones. Además, se debe agregar la figura por cada punto
    //        que la componga (Segmentos son 2 veces y triangulos 3 veces).

private:
    /**
     * Intersecta la figura f con todas las figuras del manto. Como resultado:
     *   - Las figuras del manto se fragmentan y sus partes dominadas se
     *   eliminan.
     *   - La figura f se fragmenta, sus conjuntos de fragmentos no dominados
     *   se intersectan.
     * @param f - Figura que se quiere procesar
     * @return  - Retorna los fragmentos no dominados de la figura f
     */
    list<Figure3*> processFigure(Figure3* f);

    /**
     * Intersecta la figura 1 y la figura 2 (en caso de que se pueda). Se
     * fragmenta la figura 1 dependiendo de la intersección y se comprueban los
     * fragmentos que serán dominados y los que no.
     * El tratamiento de los fragmentos generados es el siguiente:
     * - Se genera una lista con los fragmentos de la figura 1 que no son
     *   dominados.
     *
     * @param figure1   - Figura que se quiere fragmentar. Se retornarán los
     *                    fragmetnos de esta figura que no son dominados
     * @param figure2   - Figura con la que se intersectara la figura 1.
     * @return          - Retorna los fragmentos de la figura 1 que no son
     *                    dominados.
     */
    list<Figure3*> nonDominatedFragments(Figure3* figure1, Figure3* figure2);

    /**
     * Intersecta la figura f1 y la figura f2 (en caso de que se pueda). Se
     * fragmenta la figura f1 dependiendo de la intersección y se comprueban
     * los fragmentos que serán dominados y los que no.
     * @param f1        - Figura que se quiere fragmentar. Se retornarán los
     *                    fragmentos de esta figura que no son dominados.
     * @param f2        - Figura con la que se intersecta la figura f1.
     * @param fragments - Lista que se llenara con los fragmentos generados
     *                    de la figura f1 con la interseccion de la figura f2.
     * @param PROJECTION_PLANE - Indice del plano de proyeccion.
     * @return          - retorna los fragmentos de la figura f1 que no son
     *                    dominados.
     */
    void nonDominatedFragmentsProj(Figure3* f1, Figure3* f2, list<Figure2*>
            fragments, int PROJECTION_PLANE);

    /**
     * Intersecta los espacios contenidos en las dos listas. Retorna el
     * espacio generado en esta intersección.
     * @param l1    - Lista 1 que se quiere intersectar con la lista 2
     * @param l2    - Lista 2 que se quiere intersectar con la lista 1
     * @return      - Retorna la intersección de los espacios contenidos en
     *                la lista 1 y la lista 2.
     */
    list<Figure3 *> spaceIntersect(list<Figure3 *> l1, list<Figure3 *> l2);

    /**
     * Une las tres listas de figuras en dos dimensiones para generar una
     * lista de figuras en tres dimensiones.
     * @param figure - Figura madre de las listas de figuras ingresadas.
     * @param lXY    - Lista 1 de figuras (Corresponde a la proyeccion XY)
     * @param lXZ    - Lista 1 de figuras (Corresponde a la proyeccion XZ)
     * @param lYZ    - Lista 1 de figuras (Corresponde a la proyeccion YZ)
     * @return      - Retorna una lista de figuras en tres dimensiones que
     *                corresponde a la union de estas tres listas.
     */
    list<Figure3*> spaceUnion(Figure3* figure, list<Figure2*> lXY,
                              list<Figure2*> lXZ, list<Figure2*> lYZ);
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
