//
// Created by Braulio Lobo on 9/6/19.
//

#include <iostream>
#include <fstream>
#include <unordered_map>
#include "Manto.h"
#include "Tester.h"
#include "figures/figures2/Point2.h"
#include "figures/figures3/Point3.h"


Manto::~Manto() {
    if(Tester::DEBUG_DELET)
        std::cout << "Eliminado el manto" << std::endl;
}

void Manto::addFigure(Figure3 *figure) {

    // Creando lista de fragmentos no dominados
    list<Figure3*> noDominatedFragments = processFigure(figure);

    // En caso de que la figura se haya dominado, la guardamos para verla luego
    if(noDominatedFragments.empty())
        lFigure3Dominated.push_back(figure);

    // Agregando los gragmentos no dominados de la figura
    for(auto & fragment : noDominatedFragments) {
        // Agregado figura
        lFigure3.push_back(fragment);

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

    for(auto & figure : lFigure3){
        std::cout << figure->toString() << std::endl;
    }
}

void Manto::printAllGraphFigures3() {
    lFigure3.begin();

    for(auto & figure : lFigure3){
        std::cout << figure->toGraphString() << std::endl;
    }
}

void Manto::printAllFigures2(int PROJECTION_PLANE) {
    // Seleccionando mapa de figuras
    std::map<float, Figure2*> map;
    switch(PROJECTION_PLANE){
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
    // Guardando figuras reales (tercera dimension)
    myfile.open (path + "Figures.txt");
    for(auto & figure : lFigure3){
        myfile << figure->toGraphString() << std::endl;
    }
    myfile.close();

    // Guardando proyecciones en el plano xy
    myfile.open(path + "Pxy.txt");
    for (auto & i : mapFigureXY) {
        myfile << i.second->toGraphString(Figure3::PROJECTION_XY) << std::endl;
    }
    myfile.close();

    // Guardando proyecciones en el plano xz
    myfile.open(path + "Pxz.txt");
    for (auto & i : mapFigureXZ) {
        myfile << i.second->toGraphString(Figure3::PROJECTION_XZ) << std::endl;
    }
    myfile.close();

    // Guardando proyecciones en el plano yz
    myfile.open(path + "Pyz.txt");
    for (auto & i : mapFigureYZ) {
        myfile << i.second->toGraphString(Figure3::PROJECTION_YZ) << std::endl;
    }
    myfile.close();

    // Guardando proyecciones en el plano yz
    myfile.open(path + "dominated.txt");
    for (auto & i : lFigure3Dominated) {
        myfile << i->toGraphString() << std::endl;
        myfile << i->getProjection(Figure3::PROJECTION_XY)->toGraphString(Figure3::PROJECTION_XY) << std::endl;
        myfile << i->getProjection(Figure3::PROJECTION_XZ)->toGraphString(Figure3::PROJECTION_XZ) << std::endl;
        myfile << i->getProjection(Figure3::PROJECTION_YZ)->toGraphString(Figure3::PROJECTION_YZ) << std::endl;
    }
    myfile.close();
}

list<Figure3 *> Manto::processFigure(Figure3 *f) {
    list<Figure3 *> nDomFrag; // fragmentos no dominados de f
    list<Figure3 *> fToAdd;   // Figuras o fragmentos que se agregaran al manto
    list<Figure3 *> fToDel;   // Figuras que se eliminaran del manto

    // En caso de que no hayan figuras dentro del manto
    nDomFrag.push_back(f);

    // OPTIMIZE: la lista lInRegion deberá ser un resultado de un upper_bound
    //  de un KDTREE. Notar que para que se pueda fragmentar y dominar
    //  correctamente la figura f (que se esta ingresando), es necesario unir
    //  un lower_bound (inRegionf) con un upper_bound (fInRegion) del KDTREE
    //  (resultando en la lista figures).
    // list<Figure3 *> fInRegion; // Figuras en la region proyectada de f
    // list<Figure3 *> inRegionf; // Figuras en las que f está en un region
    list<Figure3 *> figures = lFigure3; // figuras afectadas y que afectan a f

    // Procesando figura f y figuras dentro del manto
    for(auto & figure : figures){
        // Intersectando areas
        nDomFrag = spaceIntersect(nDomFrag, nonDominatedFragments(f, figure));

        // Actualizando fragmentos no dominados de figure
        list<Figure3 *> fragments = nonDominatedFragments(figure, f);
        // Si figure se ha fragmentado
        if(fragments.size() > 1){
            fToDel.push_back(figure);
            for (auto &fragment : fragments) {
                fToAdd.push_back(fragment);
            }
        }
        // Si figure ha sido dominada
        if(fragments.empty()){
            fToDel.push_back(figure);
        }
    }

    // Eliminando figuras fragmentadas
    for (auto &toDel : fToDel) {
        lFigure3.remove(toDel);
        mapFigureXY.erase(toDel->getProjection(Figure3::PROJECTION_XY)->getKey());
        mapFigureXZ.erase(toDel->getProjection(Figure3::PROJECTION_XZ)->getKey());
        mapFigureYZ.erase(toDel->getProjection(Figure3::PROJECTION_YZ)->getKey());
        lFigure3Dominated.push_back(toDel);
    }

    // Agregando fragmentos generados
    for (auto &toAdd : fToAdd) {
        figures.push_back(toAdd);
    }

    return nDomFrag;
}

list<Figure3*> Manto::nonDominatedFragments(Figure3 *figure1, Figure3*figure2){
    list<Figure3*> fragments; // Fragmentos de figure 1 no dominados

    // Proyecciones
    Figure2* f1pXY = figure1->getProjection(Figure3::PROJECTION_XY);
    Figure2* f1pXZ = figure1->getProjection(Figure3::PROJECTION_XZ);
    Figure2* f1pYZ = figure1->getProjection(Figure3::PROJECTION_YZ);
    Figure2* f2pXY = figure2->getProjection(Figure3::PROJECTION_XY);
    Figure2* f2pXZ = figure2->getProjection(Figure3::PROJECTION_XZ);
    Figure2* f2pYZ = figure2->getProjection(Figure3::PROJECTION_YZ);

    // Calculando proyecciones
    list<Figure2*> intXY =
            nonDominatedFragmentsProj(f1pXY, f2pXY);
    list<Figure2*> intXZ =
            nonDominatedFragmentsProj(f1pXZ, f2pXZ);
    list<Figure2*> intYZ =
            nonDominatedFragmentsProj(f1pYZ, f2pYZ);

    fragments = spaceUnion(figure1, intXY, intXZ, intYZ);

    return fragments;
}

list<Figure3*> Manto::spaceIntersect(list<Figure3*> l1, list<Figure3*> l2){
    list<Figure3*> intersected;

    // En caso de que alguna lista venga vacia, el retorn es vacio
    if(l1.empty() || l2.empty())
        return intersected;

    // En caso de que ambas listas contengan puntos (No se fragmentan)
    Point3* p1 = dynamic_cast<Point3*>(l1.front());
    Point3* p2 = dynamic_cast<Point3*>(l2.front());
    if(p1 != nullptr && p2 != nullptr && p1->equal(p2)){
        intersected.push_back(p1);
    }

    // TODO:
    //    - Intersectar espacios de puntos (?)
    //    - Intersectar espacios de segmentos
    //    - Intersectar espacios de triangulos

    return intersected;
}

list<Figure2 *> Manto::nonDominatedFragmentsProj(Figure2 *f1, Figure2 *f2) {
    list<Figure2 *> listNDF; // Lista de fragmentos no dominados

    // Si ambas figuras son puntos
    if(dynamic_cast<Point2*>(f1) != nullptr && dynamic_cast<Point2*>(f2) != nullptr){
        Point2* p1 = dynamic_cast<Point2*>(f1);
        Point2* p2 = dynamic_cast<Point2*>(f2);

        if(!(p1->getAbscissa() > p2->getAbscissa() &&
            p1->getOrdinate() > p2->getOrdinate())){
            listNDF.push_back(f1);
        }
    }

    // TODO:
    //    - Programar fragmentos dominados para segmentos
    //    - Programar fragmentos dominados para triangulos

    return listNDF;
}

list<Figure3 *> Manto::spaceUnion(Figure3* figure, list<Figure2 *> lXY,
        list<Figure2 *> lXZ, list<Figure2 *> lYZ) {
    list<Figure3 *> lFigures3; // Lista de figuras generadas por la union

    // En caso de que las tres contengan solo un punto
    if(!lXY.empty() || !lXZ.empty() || !lYZ.empty()){
        Point3* p = dynamic_cast<Point3*>(figure);

        if(p != nullptr){
            // TODO: hacer comprobación de que los puntos coinciden

            // Creando punto en tres dimensiones y agregandolo a la lFigures3
            lFigures3.push_back(figure);
        }
    }

    // TODO:
    //    - Programar union en caso de que sean segmentos
    //    - Programar union en caso de que sean triangulos
    return lFigures3;
}
