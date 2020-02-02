//
// Created by Braulio Lobo on 9/6/19.
//

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <util/RangeContainer.h>
#include "Manto.h"
#include "Tester.h"


Manto::~Manto() {
    if (Tester::DEBUG_DELET)
        std::cout << "Eliminado el manto" << std::endl;
}

void Manto::addFigure(Figure3 *figure) {

    // Creando lista de fragmentos no dominados
    list<Figure3 *> noDominatedFragments = processFigure(figure);

    // En caso de que la figura se haya dominado, la guardamos para verla luego
    if (noDominatedFragments.empty())
        lFigure3Dominated.insert(figure);

    // Agregando los gragmentos no dominados de la figura
    for (auto &fragment : noDominatedFragments) {
        // Agregado figura
        lFigure3.insert(fragment);

        // Agregando proyecciones
        int pxy = Figure3::PROJECTION_XY;
        int pxz = Figure3::PROJECTION_XZ;
        int pyz = Figure3::PROJECTION_YZ;
        Figure2 *fpxy = fragment->getProjection(pxy);
        Figure2 *fpxz = fragment->getProjection(pxz);
        Figure2 *fpyz = fragment->getProjection(pyz);
        mapFigureXY[fpxy->getKey()] = fpxy;
        mapFigureXZ[fpxz->getKey()] = fpxz;
        mapFigureYZ[fpyz->getKey()] = fpyz;
    }
}

void Manto::printAllFigures3() {
    lFigure3.begin();

    for (auto &figure : lFigure3) {
        std::cout << figure->toString() << std::endl;
    }
}

void Manto::printAllGraphFigures3() {
    lFigure3.begin();

    for (auto &figure : lFigure3) {
        std::cout << figure->toGraphString() << std::endl;
    }
}

void Manto::printAllFigures2(int PROJECTION_PLANE) {
    // Seleccionando mapa de figuras
    std::map<float, Figure2 *> map;
    switch (PROJECTION_PLANE) {
        case Figure3::PROJECTION_XY:
            map = mapFigureXY;
            break;
        case Figure3::PROJECTION_XZ:
            map = mapFigureXY;
            break;
        case Figure3::PROJECTION_YZ:
            map = mapFigureXY;
            break;
        default:
            break;
    }

    // Imprimiendo mapa ordenado
    for (auto i = map.begin(); i != map.end(); i++) {
        std::cout << i->first << " : " << i->second->toString() << '\n';
    }
}

void Manto::saveInstance(std::string path) {
    ofstream myfile;

    // Guardando puntos no dominados
    myfile.open(path + "puntos.txt");
    for (auto &figure : lFigure3) {
        if (figure->getInstance() == Figure3::POINT_INSTANCE)
            myfile << figure->toGraphString() << std::endl;
    }
    myfile.close();

    // Guardando segmentos no dominados
    myfile.open(path + "segmentos.txt");
    for (auto &figure : lFigure3) {
        if (figure->getInstance() == Figure3::SEGMENT_INSTANCE)
            myfile << figure->toGraphString() << std::endl;
    }
    myfile.close();

    // Guardando segmentos no dominados
    myfile.open(path + "triangulos.txt");
    for (auto &figure : lFigure3) {
        if (figure->getInstance() == Figure3::TRIANGLE_INSTANCE)
            myfile << figure->toGraphString() << std::endl;
    }
    myfile.close();

    // Guardando proyecciones en el plano xy
    myfile.open(path + "Pxy.txt");
    for (auto &i : mapFigureXY) {
        myfile << i.second->toGraphString(Figure3::PROJECTION_XY) << std::endl;
    }
    myfile.close();

    // Guardando proyecciones en el plano xz
    myfile.open(path + "Pxz.txt");
    for (auto &i : mapFigureXZ) {
        myfile << i.second->toGraphString(Figure3::PROJECTION_XZ) << std::endl;
    }
    myfile.close();

    // Guardando proyecciones en el plano yz
    myfile.open(path + "Pyz.txt");
    for (auto &i : mapFigureYZ) {
        myfile << i.second->toGraphString(Figure3::PROJECTION_YZ) << std::endl;
    }
    myfile.close();

    // ---------------------- GUARDANDO FIGURAS DOMINADAS ----------------------
    // Limpiando figuras dominadas
    std::map<string, Figure3 *> mFigureDominatedCleared;

    for (const auto &figure : lFigure3Dominated) {
        mFigureDominatedCleared[figure->toGraphString()] = figure;
    }

    myfile.open(path + "puntosD.txt");
    for (auto &figureD : mFigureDominatedCleared) {
        if (figureD.second->getInstance() == Figure3::POINT_INSTANCE)
            myfile << figureD.second->toGraphString() << std::endl;
    }
    myfile.close();

    myfile.open(path + "segmentosD.txt");
    for (auto &figureD : mFigureDominatedCleared) {
        if (figureD.second->getInstance() == Figure3::SEGMENT_INSTANCE)
            myfile << figureD.second->toGraphString() << std::endl;
    }
    myfile.close();

    myfile.open(path + "triangulosD.txt");
    for (auto &figureD : mFigureDominatedCleared) {
        if (figureD.second->getInstance() == Figure3::TRIANGLE_INSTANCE)
            myfile << figureD.second->toGraphString() << std::endl;
    }
    myfile.close();
}

list<Figure3 *> Manto::processFigure(Figure3 *f) {
    list<Figure3 *> nDomFrag; // fragmentos no dominados de f
    list<Figure3 *> fToAdd;   // Figuras o fragmentos que se agregaran al manto
    list<Figure3 *> fToDel;   // Figuras que se eliminaran del manto

    lFigure3Dominated.insert(f);

    // En caso de que no hayan figuras dentro del manto
    nDomFrag.push_back(f);

    // OPTIMIZE: la lista lInRegion deberá ser un resultado de un upper_bound
    //  de un KDTREE. Notar que para que se pueda fragmentar y dominar
    //  correctamente la figura f (que se esta ingresando), es necesario unir
    //  un lower_bound (inRegionf) con un upper_bound (fInRegion) del KDTREE
    //  (resultando en la lista figures).
    // list<Figure3 *> fInRegion; // Figuras en la region proyectada de f
    // list<Figure3 *> inRegionf; // Figuras en las que f está en un region
    std::unordered_set<Figure3 *> figures = lFigure3; // figuras afectadas y
    // que afectan a f

    // Procesando figura f y figuras dentro del manto
    for (auto &figure : figures) {
        // Intersectando areas
        nDomFrag = spaceIntersect(nDomFrag, nonDominatedFragments(f, figure));

        // Actualizando fragmentos no dominados de figure
        list<Figure3 *> fragments = nonDominatedFragments(figure, f);
        // Si figure se ha fragmentado
        if (fragments.size() != 1 || (*fragments.begin()) != figure) {
            fToDel.push_back(figure);
            for (auto &fragment : fragments) {
                fToAdd.push_back(fragment);
            }
        }
        // Si figure ha sido dominada
        if (fragments.empty()) {
            fToDel.push_back(figure);
        }
    }

    // Eliminando figuras fragmentadas
    for (auto &toDel : fToDel) {
        lFigure3.erase(toDel);

    }

    // Agregando fragmentos generados
    for (auto &toAdd : fToAdd) {
        lFigure3.insert(toAdd);
    }

    return nDomFrag;
}

list<Figure3 *>
Manto::nonDominatedFragments(Figure3 *figure1, Figure3 *figure2) {
    list<Figure3 *> fragments; // Fragmentos de figure 1 no dominados

    // Obtiniendo las instancias de las figuras
    int instFigure1 = figure1->getInstance();
    int instFigure2 = figure2->getInstance();

    // Procesamiento rapido para puntos
    if (instFigure1 == Figure3::POINT_INSTANCE &&
        instFigure2 == Figure3::POINT_INSTANCE) {
        Point3 *p1 = dynamic_cast<Point3 *>(figure1);
        Point3 *p2 = dynamic_cast<Point3 *>(figure2);
        if (!(p1->getX() >= p2->getX() &&
              p1->getY() >= p2->getY() && p1->getZ() >= p2->getZ())) {
            fragments.push_back(figure1);
            return fragments;
        }
    }

    // Calculando interseccionde proyecciones
    else {
        list<Figure2 *> intXY;
        list<Figure2 *> intXZ;
        list<Figure2 *> intYZ;
        nonDominatedFragmentsProj(figure1, figure2, intXY,
                                  Figure3::PROJECTION_XY);
        nonDominatedFragmentsProj(figure1, figure2, intXZ,
                                  Figure3::PROJECTION_XZ);
        nonDominatedFragmentsProj(figure1, figure2, intYZ,
                                  Figure3::PROJECTION_YZ);

        fragments = spaceUnion(figure1, intXY, intXZ, intYZ);
    }

    return fragments;
}

list<Figure3 *> Manto::spaceIntersect(list<Figure3 *> l1, list<Figure3 *> l2) {
    list<Figure3 *> intersected;

    // En caso de que alguna lista venga vacia, el retorn es vacio
    if (l1.empty() || l2.empty())
        return intersected;

    Figure3 *fl1 = l1.front();  // Primer elemento de la lista 1
    Figure3 *fl2 = l2.front();  // Primer elemento de la lista 2

    // En caso de que ambas listas contengan puntos (No se fragmentan)
    if(fl1->getInstance() == Figure3::POINT_INSTANCE && fl2->getInstance() ==
       Figure3::POINT_INSTANCE) {
        Point3 *p1 = dynamic_cast<Point3 *>(l1.front());
        Point3 *p2 = dynamic_cast<Point3 *>(l2.front());
        if (p1->equal(p2)) {
            intersected.push_back(p1);
            return intersected;
        }
    }

    // En caso de que ambas listas contengan segmentos
    if (fl1->getInstance() == Figure3::SEGMENT_INSTANCE && fl2->getInstance() ==
         Figure3::SEGMENT_INSTANCE) {
        Segment3 *s1;
        Segment3 *s2;
        Segment3 *overlap;
        // Intersectando los segmentos
        for (auto &f1 : l1) {
            s1 = dynamic_cast<Segment3 *>(f1);
            for (auto &f2 : l2) {
                s2 = dynamic_cast<Segment3 *>(f2);
                overlap = s1->overlap(s2);

                // En caso de que haya interseccion
                if (overlap != nullptr)
                    intersected.push_front(overlap);
            }
        }

        return intersected;
    }

    if (fl1->getInstance() == Figure3::TRIANGLE_INSTANCE && fl2->getInstance() ==
        Figure3::TRIANGLE_INSTANCE){
        // TODO: programar la interseccion de triangulos
        intersected.push_front(fl1);
    }

    return intersected;
}


void Manto::nonDominatedFragmentsProj(Figure3 *f1,
                                      Figure3 *f2, list<Figure2 *> &fragments,
                                      int PROJECTION_PLANE) {
    // Obteniendo las instancias de las figuras
    int instF1 = f1->getInstance();
    int instF2 = f2->getInstance();

    // Casoss de fragmentacion para segmentos
    if (instF1 == Figure3::SEGMENT_INSTANCE) {
        Segment3 *s = dynamic_cast<Segment3*>(f1);
        Segment2 *sp = s->getProjection(PROJECTION_PLANE);
        if (instF2 == Figure3::POINT_INSTANCE) { // Figura 2 es un punto
            Point3 *p = dynamic_cast<Point3 *>(f2);
            Point2 *pp = p->getProjection(PROJECTION_PLANE);
            sp->fragmentedBy(pp, fragments);
        } else {
            Segment3 *s2 = dynamic_cast<Segment3 *>(f2);
            if (s2 != nullptr) { // Figura 2 es un segmento
                sp->fragmentedBy(s2->getProjection(PROJECTION_PLANE),
                                 fragments);
            }
        }
    }

    // Casos de dominacion de puntos
    if (instF1 == Figure3::POINT_INSTANCE) {
        Point3 *p = dynamic_cast<Point3 *>(f1);
        Point2 *pp = p->getProjection(PROJECTION_PLANE);
        if (instF2 == Figure3::SEGMENT_INSTANCE) {
            Segment3 *s = dynamic_cast<Segment3 *>(f2);
            Segment2 *sp = s->getProjection(PROJECTION_PLANE);
            bool puntoDominadoPorElSegmento = sp->domina(*pp);
            if (!puntoDominadoPorElSegmento)
                fragments.push_back(pp);
        }
        if (instF2 == Figure3::TRIANGLE_INSTANCE){
            // TODO: caso puntos triangulo
            fragments.push_front(pp);
        }

    }

    // Casos de fragmentacion de triangulos
    if (instF1 == Figure3::TRIANGLE_INSTANCE){
        Triangle3 *t = dynamic_cast<Triangle3 *>(f1);
        Triangle2 *tp = t->getProjection(PROJECTION_PLANE);

        if(instF2 == Figure3::POINT_INSTANCE){
            // TODO: caso triangulo puntos
            Point3 *p = dynamic_cast<Point3 *>(f2);
            Point2 *pp = p->getProjection(PROJECTION_PLANE);
            tp->fragmentedBy(pp, fragments);
        }

        if(instF2 == Figure3::SEGMENT_INSTANCE) {
            // TODO: caso triangulo segmento
            fragments.push_front(tp);
        }

        if(instF2 == Figure3::TRIANGLE_INSTANCE) {
            // TODO: caso triangulo triangulo
            fragments.push_front(tp);
        }
    }

}

list<Figure3 *> Manto::spaceUnion(Figure3 *figure, list<Figure2 *> lXY,
                                  list<Figure2 *> lXZ, list<Figure2 *> lYZ) {
    list<Figure3 *> lFigures3; // Lista de figuras generadas por la union

    // Si las listas no contienen elementos, retorna la lista sin elementos
    if (lXY.empty() && lXZ.empty() && lYZ.empty())
        return lFigures3;

    Point3 *point3 = dynamic_cast<Point3 *>(figure);
    if (point3 != nullptr) {
        if (!lXY.empty() || !lXZ.empty() || !lYZ.empty())
            lFigures3.push_back(figure);
        return lFigures3;
    }

    // Haciendo cast de la figura
    Segment3 *segment3 = dynamic_cast<Segment3 *>(figure);

    // Union de segmentos
    if (segment3 != nullptr) {
        float lInf;
        float lSup;
        float d1, d2;
        RangeContainer rangeContainer;

        // Agregando rangos de proyecciones en XY
        Segment2 *projection = segment3->getProjection(Figure3::PROJECTION_XY);
        for (auto &figure2 : lXY) {
            Segment2 *segment2 = dynamic_cast<Segment2 *>(figure2);
            d1 = projection->getDelta(segment2->getP1());
            d2 = projection->getDelta(segment2->getP2());
            lInf = min(d1, d2);
            lSup = max(d1, d2);

            rangeContainer.agregarRango(lInf, lSup);
        }

        // Agregando rangos de proyecciones en XZ
        projection = segment3->getProjection(Figure3::PROJECTION_XZ);
        for (auto &figure2 : lXZ) {
            Segment2 *segment2 = dynamic_cast<Segment2 *>(figure2);
            d1 = projection->getDelta(segment2->getP1());
            d2 = projection->getDelta(segment2->getP2());
            lInf = min(d1, d2);
            lSup = max(d1, d2);

            rangeContainer.agregarRango(lInf, lSup);
        }

        // Agregando rangos de proyecciones en YZ
        projection = segment3->getProjection(Figure3::PROJECTION_YZ);
        for (auto &figure2 : lYZ) {
            Segment2 *segment2 = dynamic_cast<Segment2 *>(figure2);
            d1 = projection->getDelta(segment2->getP1());
            d2 = projection->getDelta(segment2->getP2());
            lInf = min(d1, d2);
            lSup = max(d1, d2);

            rangeContainer.agregarRango(lInf, lSup);
        }

        rangeContainer.toSegments(lFigures3, *segment3);
    }

    // Union para fragmentos de triangulos
    if(figure->getInstance() == Figure3::TRIANGLE_INSTANCE){
        // TODO: programar la union para fragmentos de triangulos
        lFigures3.push_front(figure);
    }

    return lFigures3;
}

void Manto::validateInstance() {
    std::cout << "Validando instancias" << std::endl;
    int numFigurasValidadas = 0;
    int numFigurasConError = 0;
    for (auto &figure1 : lFigure3) {
        numFigurasValidadas++;
        for (auto &figure2 : lFigure3) {
            if (figure1 == figure2) continue;
            if (figure1->isDominated(figure2)) {
                numFigurasConError++;
                std::cout << "Error con figura (Dominada) " << figure1
                          << std::endl;
                break;
            }
        }
    }
    std::cout << "Figuras validadas: " << numFigurasValidadas << std::endl;
    std::cout << "Figuras con error: " << numFigurasConError << std::endl;

}
