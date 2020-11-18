//
// Created by Braulio Lobo on 07-03-20.
//

#include "Glue.h"
#include <iostream>

using namespace ClipperLib;
using namespace std;

Glue::Glue(Polygon3 *polygon3) {
    this->polygon3 = polygon3;
    this->cplr = new Clipper();
    cplr->Clear();
}

void Glue::add(Polygon2 *polygon2, int PROJECTION_PLANE) {
    Polygon3* p3 = polygon2->toPolygon3(this->polygon3, PROJECTION_PLANE);
    Polygon2* pp = p3->getProjection(unionPlane);
    Path path = pp->getPath();

    // FIXME: ptSubject o ptClip?
    /*
    std::cout << "Path agragado" << std::endl;
    for (auto &item : path) {
        std::cout << item.X << ", " << item.Y << std::endl;
    }*/

    cplr->Clear();
    cplr->AddPaths(resultado, ptClip, true);
    cplr->AddPath(path, ptSubject, true);
    cplr->Execute(ctUnion, resultado, pftNonZero, pftNonZero);
    // if(agregados == 2){
    //     cplr->AddPath(path, ptClip, true);
    // }
    // else
    //     cplr->AddPath(path, ptSubject, true);
    agregados++;

}

std::list<Figure3 *> Glue::getResult() {
    //cplr->Execute(ctUnion, resultado, pftNonZero, pftNonZero);

    list<Figure3*> polygons;
    for (auto &pathInPaths : resultado) {
        polygons.push_back(Polygon2(pathInPaths, unionPlane).toPolygon3(polygon3,
                unionPlane));
    }

    return polygons;
}

Glue::~Glue() {
    delete(cplr);
}

