//
// Created by Braulio Lobo on 9/6/19.
//

#include <iostream>
#include <fstream>
#include "Manto.h"
#include "Tester.h"


Manto::~Manto() {
    if(Tester::DEBUG_DELET)
        std::cout << "Eliminado el manto" << std::endl;
}

void Manto::addFigure(Figure3 *figure) {
    lFigure3.push_back(figure); // temporal para hacer pruebas

    // Agregando proyecciones
    int pxy = Figure3::PROJECTION_XY;
    int pxz = Figure3::PROJECTION_XZ;
    int pyz = Figure3::PROJECTION_YZ;
    Figure2* fpxy = figure->getProjection(pxy);
    Figure2* fpxz = figure->getProjection(pxz);
    Figure2* fpyz = figure->getProjection(pyz);
    mapFigureXY[fpxy->getKey()] = fpxy;
    mapFigureXZ[fpxz->getKey()] = fpxz;
    mapFigureYZ[fpyz->getKey()] = fpyz;
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
}
