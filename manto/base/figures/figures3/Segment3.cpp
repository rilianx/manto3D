//
// Created by Braulio Lobo on 10-10-19.
//

#include <sstream>
#include <Tester.h>
#include <iostream>
#include <algorithm>
#include <spaces/spaces2/Line2.h>
#include "Segment3.h"
#include "Point3.h"
#include "Polygon3.h"
#include "spaces/spaces3/Line3.h"

Segment3::Segment3(Vector3 p1, Vector3 p2){
    this->p1 = p1;
    this->p2 = p2;
    generateProjections();
}

Segment3::Segment3(float p1x, float p1y, float p1z, float p2x, float p2y,
                   float p2z) {
    this->p1 = Vector3(p1x, p1y, p1z);
    this->p2 = Vector3(p2x, p2y, p2z);
    generateProjections();
}

float Segment3::getMinX() {
    if(p1.getX() < p2.getX())
        return p1.getX();
    return p2.getX();
}

float Segment3::getMinY() {
    if(p1.getY() < p2.getY())
        return p1.getY();
    return p2.getY();
}

float Segment3::getMinZ() {
    if(p1.getZ() < p2.getZ())
        return p1.getZ();
    return p2.getZ();
}

float Segment3::getMaxX() {
    if(p1.getX() > p2.getX())
        return p1.getX();
    return p2.getX();
}

float Segment3::getMaxY() {
    if(p1.getY() > p2.getY())
        return p1.getY();
    return p2.getY();
}

float Segment3::getMaxZ() {
    if(p1.getZ() > p2.getZ())
        return p1.getZ();
    return p2.getZ();
}

bool Segment3::equal(Segment3 *segment) {
    return this->getMinX() == segment->getMinX() &&
            this->getMinY() == segment->getMinY() &&
            this->getMinZ() == segment->getMinZ() &&
           this->getMaxX()   == segment->getMaxX() &&
           this->getMaxY()   == segment->getMaxY() &&
           this->getMaxZ()   == segment->getMaxZ();
}

Segment2 *Segment3::getProjection(int PROJECTION_PLANE) {
    return &projections[PROJECTION_PLANE];
}

std::string Segment3::toString() {
    std::ostringstream ss;
    ss << "S(" << p1.getX() << ", " << p1.getY() << ", " << p1.getZ() << ")";
    ss << "->(" << p2.getX() << ", " << p2.getY() << ", " << p2.getZ() << ")";
    std::string s(ss.str());
    return s;
}

std::string Segment3::toGraphString() {
    std::ostringstream ss;
    ss << p1.getX() << ";" <<
       p1.getY() << ";" <<
       p1.getZ() << ";" <<
       p2.getX() << ";" <<
       p2.getY() << ";" <<
       p2.getZ();
    std::string s(ss.str());

    std::replace(s.begin(), s.end(), '.', ',');

    return s;
}

Segment3::~Segment3() {
    if(Tester::DEBUG_DELET)
        std::cout << "Destruido el punto 3D" << std::endl;
}

void Segment3::generateProjections() {
    const int pxy = Figure3::PROJECTION_XY;
    const int pxz = Figure3::PROJECTION_XZ;
    const int pyz = Figure3::PROJECTION_YZ;
    projections[pxy] = Segment2(p1.getX(), p1.getY(), p2.getX(), p2.getY());
    projections[pxz] = Segment2(p1.getX(), p1.getZ(), p2.getX(), p2.getZ());
    projections[pyz] = Segment2(p1.getY(), p1.getZ(), p2.getY(), p2.getZ());
}

Vector3 Segment3::getP(float delta) {
    float x = p1.getX() + delta*(p2.getX() - p1.getX());
    float y = p1.getY() + delta*(p2.getY() - p1.getY());
    float z = p1.getZ() + delta*(p2.getZ() - p1.getZ());
    return {x, y, z};
}

Segment3 *Segment3::overlap(Segment3 *segment) {
    // FIXME: esto es asumiendo que ambos segmentos son linealmente
    //  dependientes. Es decir, ambos son parte de la misma linea. Esto no
    //  siempre pasa, asi que hay que hacer un comprobador.
    //  Nota: es probable que en los casos actuales en los que se usa esta
    //  funcion no sea necesario agregar esta comprobacion

    Vector3 pp1 = getMinPX();
    Vector3 pp2 = getMaxPX();
    Vector3 pp3 = segment->getMinPX();
    Vector3 pp4 = segment->getMaxPX();

    if(pp2.getX() > pp3.getX() || pp4.getX() > pp1.getX()){
        Vector3 vInf = (pp3.getX() > pp1.getX()) ? pp3 : pp1;
        Vector3 vSup = (pp2.getX() < pp4.getX()) ? pp2 : pp4;

        return new Segment3(vInf, vSup);
    }

    return nullptr;
}

bool Segment3::isDominated(Figure3* figure) {
    std::cout << "Probando dominancia (Segmento)" << std::endl;
    return false;
}

int Segment3::getInstance() {
    return Figure3::SEGMENT_INSTANCE;
}

bool Segment3::equal(Figure3 *figure3) {
    if(figure3->getInstance() != this->getInstance())
        return false;

    // Haciendo cast del segmento ingresado
    Segment3 *s3 = dynamic_cast<Segment3*>(figure3);

    // Obteniendo puntos
    Vector3 pp1 = s3->getMinPX();
    Vector3 pp2 = s3->getMaxPX();
    Vector3 pp3 = this->getMinPX();
    Vector3 pp4 = this->getMaxPX();

    bool minEqual = pp1.getX() == pp3.getX() && pp1.getY() == pp3.getY()
                && pp1.getZ() == pp3.getZ();
    bool maxEqual = pp2.getX() == pp4.getX() && pp2.getY() == pp4.getY()
                    && pp2.getZ() == pp4.getZ();
    return minEqual && maxEqual;
}

bool Segment3::domina(Point3 *point3) {
    Point2* pxy = point3->getProjection(Figure3::PROJECTION_XY);
    Point2* pxz = point3->getProjection(Figure3::PROJECTION_XZ);
    Point2* pyz = point3->getProjection(Figure3::PROJECTION_YZ);
    bool xy = projections[PROJECTION_XY].domina(*pxy);
    bool xz = projections[PROJECTION_XZ].domina(*pxz);
    bool yz = projections[PROJECTION_YZ].domina(*pyz);
    return xy && xz && yz;
}

Line3 Segment3::getLine(){
    Vector3 director = {p1.getX() - p2.getX(),
                        p1.getY() - p2.getY(),
                        p1.getZ() - p2.getZ()};
    return {director, p1};
}

std::list<Segment3 *> Segment3::fragment(Polygon3 *polygon3) {
    std::list<Segment3 *> fragments;
    set<float> lambdas;            // Vector de lambdas del segmento

    /*
     * PROCEDIMIENTO:
     * Las fragmentaciones en primera instancia se guardan como lambdas y
     * luego se realiza la fragmentacion real.
     * - En primera instancia es fragmenta el segmento considerando las
     * proyecciones del segmento y la del poligono.
     * - En segunda instancia se fragmenta el segmetno considerando el plano
     * que contiene el poligono con el segmento.
     */

    // Fragmentación con las proyecciones
    for (const auto &projection : Figure3::PROJECTIONS) {
        // Obteniendo proyecciones
        Polygon2* pp = polygon3->getProjection(projection);
        Segment2* sp = this->getProjection(projection);

        // Obteniendo limites de las areas dominadas
        Line2 lh = pp->getLowerHLine();
        Line2 lv = pp->getLowerVLine();

        float lambda;

        // Obteniendo intersecciones de las lineas con el segmento
        Vector2* intersection1 = lh.intersect(*sp);
        Vector2* intersection2 = lv.intersect(*sp);

        if(intersection1 != nullptr){
            lambda = sp->getDelta(*intersection1);
            lambdas.insert(lambda);
        }

        if(intersection2 != nullptr){
            lambda = sp->getDelta(*intersection2);
            lambdas.insert(lambda);
        }

        // Fragmentando por interseccion con bordes del poligono
        // OPTIMIZE: Los segmento creados por getSegments() podrian no estar
        //  siendo limpiados de la memoria
        for(auto &segmentOnPolygon : pp->getSegments()){
            Vector2* intersection = sp->intersect(*segmentOnPolygon);
            if(intersection != nullptr){
                lambda = sp->getDelta(*intersection);
                lambdas.insert(lambda);
            }
        }

    }

    // Fragmentación con el plano
    Plane plane = polygon3->getPlane();
    Line3 line3 = this->getLine();
    Vector3 intersection3 = line3.intersect(plane);
    float newLambda = this->getDelta(intersection3);
    if(newLambda < 1 && newLambda > 0)
        lambdas.insert(newLambda);

    // Transormando lambdas en lista de segmentos
    float l1 = 0;
    float l2;
    for (auto &lambda : lambdas) {
        std::cout << "Lambda: " << lambda << std::endl;
        l2 = lambda;

        // Creando segmentos
        Segment3* ns = new Segment3(this->getP(l1), this->getP(l2));
        fragments.push_back(ns);

        // Actualizando pre lambda
        l1 = l2;
    }

    // Ultimo segmento
    Segment3* ns = new Segment3(this->getP(l1), this->getP(1));
    fragments.push_back(ns);

    return fragments;
}

float Segment3::getDelta(Vector3 p) {
    float delta = (p.getX() - p1.getX()) /
                  (p2.getX() - p1.getX());
    return delta;
}

Vector3 Segment3::getMidlePoint() {
    float x = this->getMinX() + (this->getMaxX() - this->getMinX()) / 2;
    float y = this->getMinY() + (this->getMaxY() - this->getMinY()) / 2;
    float z = this->getMinZ() + (this->getMaxZ() - this->getMinZ()) / 2;
    return Vector3(x, y, z);
}

