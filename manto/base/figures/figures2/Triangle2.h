//
// Created by Braulio Lobo on 25-01-20.
//

#ifndef MANTO_TRIANGLE2_H
#define MANTO_TRIANGLE2_H

#include <spaces/spaces2/Vector2.h>
#include <list>
#include "Figure2.h"

// Solucion para referencias crusadas
class Segment2;
class Point2;

class Triangle2 : public Figure2{

    // Vectores del triangulo
    Vector2 p1 = Vector2(0,0);
    Vector2 p2 = Vector2(1,1);
    Vector2 p3 = Vector2(1,2);

public:
    Triangle2(const Vector2 &p1, const Vector2 &p2, const Vector2 &p3);
    Triangle2(float p1a, float p1o, float p2a, float p2o, float p3a, float p3o);
    Triangle2();

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
     * Comprueba el triangulo domina al punto ingresado como parametro.
     * @param p - Punto que podria ser dominado por el triangulo o no.
     * @return  - Retorn True si el triangulo domina al punto y False en caso
     *            contrario.
     */
    bool domina(Point2 p);

    /**
     * Corta el triangulo en dos partes, si es que es posible. Se calucla la
     * linea que pasa por los dos puntos ingresados como parametros. Esta es
     * la linea que se usará para cortar el triangulo. Se intersecta esta
     * linea con la figura y se generan dos triangulos si es que las
     * intersecciones son correctas.
     * @param p1    - Punto 1 por el que pasa la recta
     * @param p2    - Punto 2 por el que pasa la recta
     * @return      - Retorna tres triangulos si es que es que la linea
     *                generada intersecta con la figura. Retorna null en caso
     *                contrario.
     */
    Triangle2** split(Vector2 p1, Vector2 p2);

    const Vector2 &getP1() const;
    const Vector2 &getP2() const;
    const Vector2 &getP3() const;

    /**
     * Genera la llave que se utiliza para identifica este punto en el mapa
     * ordenado. Esta corresponde al valor de su abscissa.
     * @return  - Retorna la llave generada.
     */
    virtual float getKey();
    virtual std::string toString();
    virtual std::string toGraphString(int PROJECTION_PLANE);

};


#endif //MANTO_TRIANGLE2_H
