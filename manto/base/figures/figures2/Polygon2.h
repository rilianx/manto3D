//
// Created by Braulio Lobo on 02-02-20.
//

#ifndef MANTO_POLYGON2_H
#define MANTO_POLYGON2_H

#include "util/clipper/clipper.hpp"
#include <list>
#include "Figure2.h"
#include "Triangle2.h"
#include "Point2.h"
#include "Vector3.h"
#include <Figure3.h>

class Polygon3;
class Segment2;

class Polygon2 : public Figure2{

    // Vectores que forman el poligono
    ClipperLib::Path path;          // Vectores del poligono
    ClipperLib::Paths solutions;    // Soluciones de las operaciones

    // El valor de precision tiene que ser potencia de 10. Este se utiliza
    // como multiplicador y divisor, con el fin de obtener mayor o menor
    // precision en los calculos de las operaciones realizadas a los
    // poligonos (Como unionWith, intersect, difference, etc)
    float precision = 10000;

    float MAX_VALUE = 99999;

private:

    static std::list<Polygon2*> pathsToPolygons(const ClipperLib::Paths& paths);

public:

    /**
     * Cosntructor simple y por defecto
     */
    Polygon2();

    /**
     * Constructor de poligono
     * @param vectores  - Arreglo de vectores. Corresponden a enteros
     *                    pareados, de la forma: {x1,y1,x2,y2..., xn, yn}.
     * @param nVectores - Numero de vectores que conforman el poligono.
     */
    Polygon2(const int* vectores, int nVectores);

    /**
     * Constructor de poligono
     * @param vectores  - Arreglo de vectores. Corresponden a enteros
     *                    pareados, de la forma: {x1,y1,x2,y2..., xn, yn}.
     * @param nVectores - Numero de vectores que conforman el poligono.
     */
    Polygon2(const float* vectores, int nVectores);

    /**
     * Constructor de poligonos con path
     */
    explicit Polygon2(ClipperLib::Path path);

    /**
     * Genera una interseccion entre el poligono (this) y el ingresado como
     * parametro.
     * @param polygon   - Poligono con el que se quiere hacer la interseccion.
     * @return          - Retorna los poligonos generados por la interseccion.
     */
    std::list<Polygon2*> intersect(const Polygon2& polygon);

    /**
     * Genera una union entre el poligono (this) y el ingresado como
     * parametro.
     * @param polygon   - Poligono con el que se quiere hacer la union.
     * @return          - Retorna los poligonos generados por la union.
     */
    std::list<Polygon2*> unionWith(const Polygon2& polygon);

    /**
     * Genera la diferencia entre el poligono (this) y el ingresado como
     * parametro.
     * @param polygon   - Poligono con el que se quiere hacer la diferencia.
     * @return          - Retorna los poligonos generados por la diferencia.
     */
    std::list<Polygon2*> difference(const Polygon2& polygon);

    /**
     * Rellena la lista fragments con fragmentos no dominados, los cuales son
     * producto de una fragmentacion generada por el punto ingrasado como
     * parametro.
     * @param p             - Punto que fragmenta al poligono
     * @param fragments     - Lista de fragmentos que se va a llenar.
     */
    void fragmentedBy(Point2* p, std::list<Figure2*> &fragments);

    /**
     * Rellena la lista fragments con fragmentos no dominados, los cuales son
     * producto de una fragmentacion generada por el segmento ingrasado como
     * parametro.
     * @param s             - Segmento que fragmenta al poligono
     * @param fragments     - Lista de fragmentos que se va a llenar.
     */
    void fragmentedBy(Segment2* s, std::list<Figure2*> &fragments);

    /**
     * Rellena la lista fragments con fragmentos no dominados, los cuales son
     * producto de una fragmentacion generada por el triangulo ingrasado como
     * parametro.
     * @param t             - Triangulo que fragmenta al poligono
     * @param fragments     - Lista de fragmentos que se va a llenar.
     */
    void fragmentedBy(Triangle2* t, std::list<Figure2*> &fragments);

    /**
     * Rellena la lista fragments con fragmentos no dominados, los cuales son
     * producto de una fragmentacion generada por el poligono ingrasado como
     * parametro.
     * @param p             - Poligono que fragmeta al poligono
     * @param fragments     - Lista de fragmentos que se va a llenar.
     */
    void fragmentedBy(Polygon2* p, std::list<Figure2*> &fragments);

    /**
     * Calcula la proyeccion de este poligono en el plano del ingresado como
     * parametro
     * @param p3    - Poligono contenido en el plano donde se generará el
     *                poligono en tres dimensiones.
     * @param PROJECTION_PLANE - Plano al que pertenece esta proyeccion
     * @return      - Retorna un poligono de tres dimensiones.
     */
    Polygon3* toPolygon3(Polygon3* p3, int PROJECTION_PLANE);

    /**
     * Obtiene el indice del vector que contiene la menor abscisa en el Path
     * del poligono
     * @return  - Retorna un entero correspondiente al indice del vector que
     *            contiene la menor abscisa del path del poligono.
     */
    int getMenorAbscissa();

    /**
     * Obtiene el indice del vector que contiene la menor ordenada en el Path
     * del poligono
     * @return  - Retorna un entero correspondiente al indice del vector que
     *            contiene la menor ordenada del path del poligono
     */
    int getMenorOrdinate();

    /**
     * Obtiene el valor de la abscisa del vector que tiene el indice
     * ingresado como parametro
     * @param index - Indice del vector que se quiere obtener la abscisa
     * @return      - Retorna el valor de la abscisa del path[index]
     */
    float getAbscissa(int index);

    /**
     * Obtiene el valor de la ordenada del vector que tiene el indice
     * ingresado como parametro
     * @param index - Indice del vector que se quiere obtener la ordenada
     * @return      - Retorna el valor de la ordenada del path[index]
     */
    float getOrdinate(int index);

    /**
     * Comprueba si el punto ingresado está dentro del poligono
     * @param pos   - Posicion del punto que se quiere comprobar si está
     *                dentro del poligono
     * @return      - Retorna True si el poligono contiene el las coordenadas
     *                ingresadas y False en caso contrario.
     */
    bool onPolygon(Vector2 pos);

    /**
     * Comprueba si el punto ingresado está dentro del poligono
     * @param x     - Coordenada en el eje X del punto a comprobar
     * @param y     - Coordenada en el eje Y del punto a comprobar
     * @return      - Retorna True si el poligono contiene el las coordenadas
     *                ingresadas y False en caso contrario.
     */
    bool onPolygon(float x, float y);

    /**
     * Obtiene el camino, o conjunto de vectores, inferior del poligono.
     * @return  - Retorna una lista con los vectores seleccionados
     */
    std::list<Vector2> getBottomPath();

    const ClipperLib::Path &getPath() const;

    // Funciones virutales
    virtual float getKey();
    virtual std::string toString();
    virtual std::string toGraphString(int PROJECTION_PLANE);

    bool domina(Point2 point2);
};


#endif //MANTO_POLYGON2_H
