//
// Created by Braulio Lobo on 11-10-19.
//

#ifndef MANTO_SEGMENT2_H
#define MANTO_SEGMENT2_H


#include <spaces/spaces2/Vector2.h>
#include <list>
#include "Figure2.h"
#include "Point2.h"
#include "Triangle2.h"
#include "Polygon2.h"

class Segment2 : public Figure2 {

    // Vectores del segmento
    Vector2 p1 = Vector2(0,0);
    Vector2 p2 = Vector2(1,1);

private:

    /**
     * @return - Retorna el punto del segmento que contiene el menor valor en
     *           la coordenada ordenada.
     */
    Vector2 getMenorOrdinate();

    /**
     * @return - Retorna el punto del segmento que contiene el mayor valor en
     *           la coordenada ordenada.
     */
    Vector2 getMayorOrdinate();

public:
    Segment2(float ab1, float or1, float ab2, float or2);
    Segment2(Vector2 p1, Vector2 p2);
    Segment2();
    ~Segment2();

    const Vector2 &getP1() const;
    const Vector2 &getP2() const;

    /**
     * Rellena la lista fragments con fragmentos no dominados, los cuales son
     * producto de una fragmentacion generada por el punto ingrasado como
     * parametro.
     * @param p             - Punto que fragmenta al segmento
     * @param fragments     - Lista de fragmentos que se va a llenar.
     */
    void fragmentedBy(Point2* p, std::list<Figure2*> &fragments);

    /**
     * Rellena la lista fragments con fragmentos no dominados, los cuales son
     * producto de una fragmentacion generada por el segmento ingrasado como
     * parametro.
     * @param s             - Segmento que fragmenta al segmento
     * @param fragments     - Lista de fragmentos que se va a llenar.
     */
    void fragmentedBy(Segment2* s, std::list<Figure2*> &fragments);

    /**
      * Rellena la lista fragments con fragmentos no dominados, los cuales son
     * producto de una fragmentacion generada por el triangulo ingrasado como
     * parametro.
     * @param t             - Triangulo que fragmenta al segmento
     * @param fragments     - Lista de fragmentos que se va a llenar.
     */
    void fragmentedBy(Triangle2* t, std::list<Figure2*> &fragments);

    /**
     * Rellena la lista fragments con fragmentos no dominados, los cuales son
     * producto de una fragmentacion generada por el poligono ingresado como
     * parametro.
     * @param p             - Poligono que fragmenta al segmento
     * @param fragments     - Lista de fragmentos que se va a llenar.
     */
    void fragmentedBy(Polygon2* p, std::list<Figure2*> &fragments);

    /**
     * Calcula el parametro delta que debería tener el vector p1-p2 para llegar
     * a p. Esto es desde el punto p1, es decir p1+delta(p1-p2)=p.
     * @param p - Punto hasta donde se quiere calcular del parametro delta
     * @return  - Retorna el parametro delta calculado.
     */
    float getDelta(Vector2 p);

    /**
     * Obtiene el punto generado por p1+delta(p2-p1)=p
     * @param delta     - Parametro multiplicador del vector director (p2-p1)
     * @return          - Retora el punto generado por la ecuacion:
     *                    p1 + delta(p2 - p1) = p
     */
    Vector2* getP(float delta);

    /**
     * Comprueba si el segmento es intersectado con el segmento ingresado
     * como parametro.
     * @param segment2  - Segmento con el que podria ser intersectado el
     *                    actual (This).
     * @return          - Retorna el Vector resultante de la interseccion de
     *                    los segmentos. En caso de que no se intersecten
     *                    retorna null.
     */
    Vector2* intersect(Segment2 segment2);

    /**
     * Genera la llave que se utiliza para identifica este punto en el mapa
     * ordenado. Esta corresponde al valor de su abscissa.
     * @return  - Retorna la llave generada.
     */
    virtual float getKey();
    virtual std::string toString();
    virtual std::string toGraphString(int PROJECTION_PLANE);

    /**
     * @return - Retorna el punto del segmento que contiene el menor valor en
     *           la coordenada abscissa.
     */
    Vector2 getMenorAbscissa();

    /**
     * @return - Retorna el punto del segmento que contiene el mayor valor en
     *           la coordenada abscissa.
     */
    Vector2 getMayorAbscissa();

    /**
     * Comprueba el segmento domina al punto ingresado como parametro.
     * @param p - Punto que podria ser dominado por el segmento o no.
     * @return  - Retorn True si el segmento domina al punto y False en caso
     *            contrario.
     */
    bool domina(Point2 p);
};


#endif //MANTO_SEGMENT2_H
