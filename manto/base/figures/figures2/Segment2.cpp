//
// Created by Braulio Lobo on 11-10-19.
//

#include <Tester.h>
#include <iostream>
#include <sstream>
#include <figures/figures3/Figure3.h>
#include "Segment2.h"

std::string Segment2::toGraphString(int PROJECTION_PLANE) {
    std::ostringstream ss;

    switch(PROJECTION_PLANE){
        case Figure3::PROJECTION_XY:
            ss << getStringCoordenateToGraph(p1.getAbscissa(), p1.getOrdinate(),0);
            ss << getStringCoordenateToGraph(p2.getAbscissa(), p2.getOrdinate(),0);
            break;
        case Figure3::PROJECTION_XZ:
            ss << getStringCoordenateToGraph(p1.getAbscissa(), 0, p1.getOrdinate());
            ss << getStringCoordenateToGraph(p2.getAbscissa(), 0, p2.getOrdinate());
            break;
        case Figure3::PROJECTION_YZ:
            ss << getStringCoordenateToGraph(0, p1.getAbscissa(), p1.getOrdinate());
            ss << getStringCoordenateToGraph(0, p2.getAbscissa(), p2.getOrdinate());
            break;
        default:
            return "Error de Segment2_52";
    }
    std::string s(ss.str());
    return s;
}

std::string Segment2::toString() {
    std::ostringstream ss;
    ss << "S(" << p1.getAbscissa() << ", " << p1.getOrdinate() << ")";
    ss << "->(" << p2.getAbscissa() << ", " << p2.getOrdinate() << ")";
    std::string s(ss.str());
    return s;
}

float Segment2::getKey() {
    return std::min(p1.getAbscissa(), p2.getAbscissa());
}

Segment2::Segment2(float ab1, float or1, float ab2, float or2) {
    this->p1 = Vector2(ab1, or1);
    this->p2 = Vector2(ab2, or2);
}

Segment2::Segment2(Vector2 p1, Vector2 p2) {
    this->p1 = p1;
    this->p2 = p2;
}

Segment2::Segment2() {

}

Segment2::~Segment2() {
    if(Tester::DEBUG_DELET){
        std::cout << "Punto eliminado" << std::endl;
    }
}

const Vector2 &Segment2::getP1() const {
    return p1;
}

const Vector2 &Segment2::getP2() const {
    return p2;
}

float Segment2::getDelta(Vector2 p) {
    float delta = (p.getAbscissa() - p1.getAbscissa()) /
            (p2.getAbscissa() - p1.getAbscissa());
    return delta;
}

void Segment2::fragmentedBy(Point2 *p, std::list<Figure2*> &fragments) {
    // Calculando los delta (o lambda)
    float d1 = (p->getAbscissa() - p1.getAbscissa()) /
                (p2.getAbscissa() - p1.getAbscissa());
    float d2 = (p->getOrdinate() - p1.getOrdinate()) /
                (p2.getOrdinate() - p1.getOrdinate());

    // Generando los puntos
    Vector2* pA = getP(d1);
    Vector2* pB = getP(d2);

    // Obteniendo extremos de los puntos del segmento
    Vector2 pp1 = getMenorAbscissa();
    Vector2 pp2 = getMayorAbscissa();

    if(pp1.getOrdinate() > pp2.getOrdinate()) {
        // Caso 1 (6 y 7): El punto no domina
        if ((p->getOrdinate() > pA->getOrdinate()) ||   // Caso 1
            (pp1.getAbscissa() > pA->getAbscissa() &&   // Caso 6
             pp1.getAbscissa() > pB->getAbscissa()) ||
            (pp2.getAbscissa() < pA->getAbscissa() &&   // Caso 7
             pp2.getAbscissa() < pB->getAbscissa())) {
            fragments.push_back(this);
            return;
        }

        // Caso 2: El punto domina completamente el segmento
        if (pp1.getAbscissa() >= pA->getAbscissa() &&
            pp2.getAbscissa() <= pB->getAbscissa()) {
            return;
        }

        // Caso 3: El punto domina parcialmente al segmento, dividiendolo en dos
        // partes.
        if (pp1.getAbscissa() < pA->getAbscissa() &&
            pp2.getAbscissa() > pB->getAbscissa()) {
            Segment2 *s1 = new Segment2(pp1, *pA);
            Segment2 *s2 = new Segment2(*pB, pp2);
            fragments.push_back(s1);
            fragments.push_back(s2);
            return;
        }

        // Caso 4: El punto domina parcialmente al segmento, dominando solo el
        // primer extremo de este.
        if (pp1.getAbscissa() > pA->getAbscissa() &&
            pp2.getAbscissa() > pB->getAbscissa()) {
            fragments.push_back(new Segment2(*pB, pp2));
            return;
        }

        // Caso 5: El punto domina parcialmente al segmento, dominando solo le
        // ultimo extremo de este.
        if (pp1.getAbscissa() < pA->getAbscissa() &&
            pp2.getAbscissa() < pB->getAbscissa()) {
            fragments.push_back(new Segment2(pp1, *pA));
            return;
        }
    }
    else{
        // Caso 1 y 2: El punto no domina al segmento
        if((p->getOrdinate() > pA->getOrdinate() &&
            pp2.getAbscissa() < pB->getAbscissa()) ||
            (pp2.getAbscissa() < pA->getAbscissa())){
            fragments.push_back(this);
            return;
        }

        // Caso 3: El punto domina el ultimo extremo del segmento. El punto
        // esta arriba del segmento.
        if(pp1.getAbscissa() < pB->getAbscissa() &&
            pp2.getAbscissa() > pB->getAbscissa() &&
            pA->getOrdinate() < p->getOrdinate()){
            fragments.push_back(new Segment2(pp1, *pB));
            return;
        }

        // Caso 4: El punto domina el ultimo extremo del segmento. El punto
        // esta por debajo del segmento.
        if(pp1.getAbscissa() < pA->getAbscissa() &&
            pp2.getAbscissa() > pA->getAbscissa() &&
            pA->getOrdinate() > p->getOrdinate()){
            fragments.push_back(new Segment2(pp1, *pA));
            return;
        }

        // Caso 5 y 6: El punto domina completamente al segmento
        if(pA->getAbscissa() < pp1.getAbscissa() &&
            pB->getAbscissa() < pp1.getAbscissa()){
            return;
        }
    }
}

void Segment2::fragmentedBy(Segment2 *s, std::list<Figure2*> &fragments) {
    Vector2 pp1 = getMenorAbscissa();
    Vector2 pp2 = getMayorAbscissa();
    Vector2 pp3 = s->getMenorAbscissa();
    Vector2 pp4 = s->getMayorAbscissa();

    // Caso especial: El segmento S es ascentente, por tanto puede ser
    // procesado como si fuese un simple punto.
    if(pp3.getOrdinate() < pp4.getOrdinate()){
        Point2* p = new Point2(pp3);
        this->fragmentedBy(p, fragments);
        return;
    }

    float d1 = (pp3.getAbscissa() - pp1.getAbscissa()) /
            (pp2.getAbscissa() - pp1.getAbscissa());
    float d2 = (pp4.getOrdinate() - pp1.getOrdinate()) /
            (pp2.getOrdinate() - pp1.getOrdinate());

    // Puntos de interseccion entre los extremos del area dominada y el segmento
    Vector2 *pA = getP(d1);
    Vector2 *pB = getP(d2);

    // Punto de interseccion de los segmentos
    Vector2 *pI = intersect(*s);

    // Casos en los que el segmetno a fragmentar es ascendente.
    if(pp1.getOrdinate() < pp2.getOrdinate()){

        // En caso de que los segmentos se intersecten
        if(pI != nullptr){
            fragments.push_back(new Segment2(pp1, *pI));
            return;
        }

        // En caso de que el segmento domine parte o totalidad de estos con
        // alguno de sus extremos del area que domina. (Casos en que esta por
        // arriba o por abajo)
        if(pA->getOrdinate() > pp3.getOrdinate()){
            // Lo Domina completamente
            if(pA->getAbscissa() < pp1.getAbscissa()){
                return;
            }
            // Lo Domina parcialmente
            else{
                fragments.push_back(new Segment2(pp1, *pA));
                return;
            }
        }
        if(pB->getAbscissa() > pp4.getAbscissa()){
            // Lo domina completamente
            if(pB->getAbscissa() < pp1.getAbscissa()){
                return;
            }
            // Lo Domina parcialmente
            else{
                fragments.push_back(new Segment2(pp1, *pB));
                return;
            }
        }

        // Casos especiales. En estos no se intersectan, pero el segmento s
        // intersecta la lina que contiene al segmento.
        if(pA->getOrdinate() < pp3.getOrdinate() &&
            pB->getAbscissa() < pp4.getAbscissa()){
            // El Segmento s domina completamente al segmento
            if(pA->getAbscissa() < pp1.getAbscissa()){
                return;
            }

            // El Segmento s no domina ninguna parte del segmento
            else{
                fragments.push_back(this);
            }
        }
    }

    // Los siguientes casos son cuando el segmento a fragmentar es descendente
    // Casos en los que los segmentos no se intersectan
    if(pI == nullptr){
        // Caso 0: El segmento s esta por arriba de este (this).
        if((pB->getAbscissa() < pp4.getAbscissa() &&    // Caso 0
            pA->getOrdinate() < pp3.getOrdinate()) ||
            (pA->getOrdinate() < pp3.getOrdinate() &&   // Caso 0.1
            pp4.getAbscissa() > pp2.getAbscissa() &&
            pB->getAbscissa() > pp4.getAbscissa()) ||
            (pp3.getAbscissa() < pp1.getAbscissa() &&   // Caso 0.2
            pA->getOrdinate() > pp3.getOrdinate() &&
            pB->getAbscissa() < pp4.getAbscissa())){
            fragments.push_back(this);
            return;
        }

        // Caso 1: El segmento s domina completamente a este.
        if(pA->getAbscissa() < pp1.getAbscissa() &&
            pB->getAbscissa() > pp2.getAbscissa()){
            return;
        }

        // Caso 2: el segmento s domina el extremo final de este.
        if(pA->getAbscissa() > pp1.getAbscissa() &&
            pA->getAbscissa() < pp2.getAbscissa() &&
            pB->getAbscissa() > pp2.getAbscissa()){
            fragments.push_back(new Segment2(pp1, *pA));
            return;
        }

        // Caso 3: el segmento s domina el centro de este, dividiendolo en
        // dos partes
        if(pA->getAbscissa() > pp1.getAbscissa() &&
           pB->getAbscissa() < pp2.getAbscissa()){
            fragments.push_back(new Segment2(pp1, *pA));
            fragments.push_back(new Segment2(*pB, pp2));
            return;
        }

        // Caso 4: el segmento s domina el extremo inicial de este.
        if(pB->getAbscissa() > pp1.getAbscissa() &&
            pB->getAbscissa() < pp2.getAbscissa() &&
            pA->getAbscissa() < pp1.getAbscissa()){
            fragments.push_back(new Segment2(*pB, pp2));
            return;
        }

        // Caso 5 y 6: El segmento s no domina a este.
        if(pB->getAbscissa() < pp1.getAbscissa() ||
           pA->getAbscissa() > pp2.getAbscissa()){
            fragments.push_back(this);
            return;
        }
    }
    else{ // Casos en los que los segmentos se intersectan
        // Casos descendentes
        if(pp3.getOrdinate() > pA->getOrdinate()){
            // Caso 1: El segmento s domina la totalidad del extremo final
            // del segmento
            if(pB->getAbscissa() > pp2.getAbscissa()){
               fragments.push_back(new Segment2(pp1, *pI));
               return;
            }

            // Caso 2: El segmento s domina parcialmente al segmento,
            // dividiendolo en dos partes.
            else{
                fragments.push_back(new Segment2(pp1, *pI));
                fragments.push_back(new Segment2(*pB, pp2));
                return;
            }
        }

        // Casos Ascendentes
        else{
            // Caso 1: El segmento s domina la totalidad del extremo inciial
            // del segmento.
            if(pA->getAbscissa() < pp1.getAbscissa()){
                fragments.push_back(new Segment2(*pI, pp2));
                return;
            }

            // Caso 2: El segmento s domina parcialmente al segmento,
            // dividiendolo en dos partes.
            else{
                fragments.push_back(new Segment2(pp1, *pA));
                fragments.push_back(new Segment2(*pI, pp2));
                return;
            }
        }
    }
}

Vector2* Segment2::intersect(Segment2 s) {
    // La resolucion de la interseccion esta realizada por un sistema de
    // ecuaciones, el cual esta resuelto mediante el metodo de cramer.
    Vector2 pp1 = getMenorAbscissa();
    Vector2 pp2 = getMayorAbscissa();
    Vector2 pp3 = s.getMenorAbscissa();
    Vector2 pp4 = s.getMayorAbscissa();

    float ax = pp2.getAbscissa() - pp1.getAbscissa();
    float bx = pp4.getAbscissa() - pp3.getAbscissa();
    float cx = pp3.getAbscissa() - pp1.getAbscissa();
    float ay = pp2.getOrdinate() - pp1.getOrdinate();
    float by = pp4.getOrdinate() - pp3.getOrdinate();
    float cy = pp3.getOrdinate() - pp1.getOrdinate();

    float det = -ax * by + bx * ay;

    float lambda1 = (cx * (-by) + bx * cy) / det;
    float lambda2 = (ax * cy - cx * ay) / det;

    // Punto de interseccion
    float px = pp1.getAbscissa() + lambda1 *
            (pp2.getAbscissa() - pp1.getAbscissa());

    // En caso que haya interseccion se retorna el vector de la interseccion
    if(px < pp2.getAbscissa() && px > pp1.getAbscissa()){
        float py = pp1.getOrdinate() + lambda1 *
           (pp2.getOrdinate() - pp1.getOrdinate());
        return new Vector2(px, py);
    }

    // En caso de que no hay interseccion se retorna null
    return nullptr;
}

Vector2 *Segment2::getP(float delta) {
    float abscissa = p1.getAbscissa() + delta*(p2.getAbscissa() -
            p1.getAbscissa());
    float ordinate = p1.getOrdinate() + delta*(p2.getOrdinate() -
            p1.getOrdinate());
    return new Vector2(abscissa, ordinate);
}

Vector2 Segment2::getMenorAbscissa() {
    if(p1.getAbscissa() < p2.getAbscissa())
        return p1;
    return p2;
}

Vector2 Segment2::getMayorAbscissa() {
    if(p1.getAbscissa() > p2.getAbscissa())
        return p1;
    return p2;
}

Vector2 Segment2::getMenorOrdinate() {
    if(p1.getOrdinate() < p2.getOrdinate())
        return p1;
    return p2;
}

Vector2 Segment2::getMayorOrdinate() {
    if(p1.getOrdinate() > p2.getOrdinate())
        return p1;
    return p2;
}

bool Segment2::domina(Point2 p) {
    Vector2 pp1 = getMenorAbscissa();
    Vector2 pp2 = getMayorAbscissa();

    // En caso de que el segmento sea ascendente
    if(pp1.getOrdinate() < pp2.getOrdinate()){
        return p.getAbscissa() > pp1.getAbscissa() &&
            p.getOrdinate() > pp1.getOrdinate();
    }

    // Caso en que el punto este antes del segmento
    if(p.getAbscissa() < pp1.getAbscissa())
        return false;

    // Caso en que el punto este despues del segmento
    if(p.getAbscissa() > pp2.getAbscissa())
        return p.getOrdinate() > pp2.getOrdinate(); //&&
               // p.getOrdinate() > pp1.getOrdinate();

    // Obteniendo delta o lambda del punto generado por la vertical que pasa
    // por el punto
    float delta = (p.getAbscissa() - getP1().getAbscissa()) /
                  (getP2().getAbscissa() - getP1().getAbscissa());
    Vector2* pA = getP(delta);
    return pA->getOrdinate() < p.getOrdinate();
}
