//
// Created by Braulio Lobo on 10-10-19.
//

#include <sstream>
#include <Tester.h>
#include <iostream>
#include <map>
#include "Segment3.h"

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

