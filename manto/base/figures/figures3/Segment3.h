//
// Created by Braulio Lobo on 10-10-19.
//

#ifndef MANTO_SEGMENT3_H
#define MANTO_SEGMENT3_H


#include <spaces/spaces3/Vector3.h>
#include <figures/figures2/Segment2.h>
#include "Figure3.h"

class Point3;
class Polygon3;
class Line3;

class Segment3 : public Figure3{

    Vector3 p1 = Vector3(0,0,0);
    Vector3 p2 = Vector3(1,1,1);
    Segment2 projections[3];

private:
    /**
     * Genera las proyecciones del segmento y las guarda en el arreglo de
     * proyecciones
     */
    void generateProjections();

public:
    Segment3(float p1x, float p1y, float p1z, float p2x, float p2y, float p2z);
    Segment3(Vector3 p1, Vector3 p2);
    ~Segment3();

    float getMinX();
    float getMinY();
    float getMinZ();
    float getMaxX();
    float getMaxY();
    float getMaxZ();

    Vector3 getMinPX(){
        if(p1.getX() < p2.getX())
            return p1;
        return p2;
    }

    Vector3 getMaxPX(){
        if(p1.getX() > p2.getX())
            return p1;
        return p2;
    }

    bool equal(Segment3* segment);

    /**
     * Obtiene el punto generado por p1+delta(p2-p1)=p
     * @param delta     - Parametro multiplicador del vector director (p2-p1)
     * @return          - Retora el punto generado por la ecuacion:
     *                    p1 + delta(p2 - p1) = p
     */
    Vector3 getP(float delta);

    /**
     * Obtiene las proyecciones de la figura
     * @param PROJECTION_PLANE  - Indice constante del plano donde se quiere
     *                            obtener la proyeccion (Por ejemplo:
     *                            PROJECTION_XY)
     * @return                  - Retorna la proyeccion de la punto en el
     *                            plano indicado en el parametro
     */
    virtual Segment2* getProjection(int PROJECTION_PLANE);

    virtual std::string toString();
    virtual std::string toGraphString();

    virtual bool isDominated(Figure3* figure);
    virtual int getInstance();
    virtual bool equal(Figure3 *figure3);

    /**
     * Comprueba si domina el punto
     * @param point3    - Punto que probablemente esta dominado por el segmento
     * @return          - Retorna True si el segmento domina al punto y False
     *                    en caso contrario.
     */
    bool domina(Point3* point3);

    /**
     * Fragmenta el segmento en los puntos criticos marcados por el poligono
     * ingresado como parametro
     * @param polygon3  - Poligono
     * @return          - Returna una lista de segmentos correspondientes a
     *                  la fragmentación de este
     */
    std::list<Segment3*> fragment(Polygon3* polygon3);

    /**
     * Intersecta este segmento con el pasado como paremtro. Retorna el
     * resultado de la interseccion.
     * @param segment   - Segmento que se
     * @return
     */
    Segment3* overlap(Segment3* segment);

    /**
     * Genera una linea que contenga al segmento
     * @return  - Retorna una linea que contiene al segmento
     */
    Line3 getLine();

    /**
     * Calcula el parametro delta que debería tener el vector p1-p2 para llegar
     * a p. Esto es desde el punto p1, es decir p1+delta(p1-p2)=p.
     * @param p - Punto hasta donde se quiere calcular del parametro delta
     * @return  - Retorna el parametro delta calculado.
     */
    float getDelta(Vector3 p);
};

#endif //MANTO_SEGMENT3_H
