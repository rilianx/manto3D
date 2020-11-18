//
// Created by Braulio Lobo on 25-02-20.
//

#ifndef MANTO_POLYGON3_H
#define MANTO_POLYGON3_H

#include <spaces/spaces3/Vector3.h>
#include <spaces/spaces3/Plane.h>
#include "figures/figures2/Polygon2.h"
#include "Figure3.h"


class Polygon3 : public Figure3{

    int nVectors = 0;
    Vector3* vectors;
    Polygon2 projections[3];

private:
    /**
     * Genera las proyecciones del segmento y las guarda en el arreglo de
     * proyecciones
     */
    void generateProjections();

public:

    Polygon3(Vector3* vectors, int nVectors);
    Polygon3(std::list<Vector3> vectorList, int nVectors);
    ~Polygon3();

    /**
     * Obtiene las proyecciones de la figura
     * @param PROJECTION_PLANE  - Indice constante del plano donde se quiere
     *                            obtener la proyeccion (Por ejemplo:
     *                            PROJECTION_XY)
     * @return                  - Retorna la proyeccion de la punto en el
     *                            plano indicado en el parametro
     */
    virtual Polygon2* getProjection(int PROJECTION_PLANE);
    virtual std::string toString();
    virtual std::string toGraphString();

    virtual int getInstance();
    virtual bool equal(Figure3 *figure3);
    virtual bool isDominated(Figure3* figure);

    /**
     * Comprueba si domina al punto ingresado como parametro
     * @param figure    - Punto que podría o no estar dominado por el polgono
     * @return          - Retorna True si domina al punto y False en caso
     *                    contrario.
     */
    bool domina(Point3* figure);

    /**
     * Fragmenta este poligono en relación a el área dominada por el poligono
     * ingresado como prametro.
     * Notar que esta funcion no domina las partes del poligono, simplemente
     * se encarga de hacer la fragmentación
     * @param polygon3  - Poligono que va a fragmentar a este
     * @return          - Retorna una lista de fragmentos
     */
    std::list<Polygon3*> fragment(Polygon3* polygon3);

    /**
     * Corta el poligono en tres dimension
     * @param plane
     * @return
     */
    std::list<Polygon3*> split(Plane plane);

    /**
     * Obtiene un punto contenido dentro de este poligono
     * @return  - Retorna un punto obtenido en este poligono
     */
    Point3 getAPoint();

    Vector3 *getVectors() const;

    /**
     * Obtiene el plano que contiene al poligono
     * @return  - Retorna el
     */
    Plane getPlane();

    bool inBox(Point3 point3);
};


#endif //MANTO_POLYGON3_H
