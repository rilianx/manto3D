//
// Created by Braulio Lobo on 20-03-20.
//

#include "Intersector.h"

using namespace ClipperLib;
using namespace std;

std::list<Figure3 *> Intersector::getResult() {
    cplr->Execute(ctIntersection, resultado, pftEvenOdd, pftEvenOdd);

    list<Figure3*> polygons;
    for (auto &pathInPaths : resultado) {
        polygons.push_back(Polygon2(pathInPaths).toPolygon3(polygon3,
                                                            Figure3::PROJECTION_XY));
    }

    return polygons;
}

void Intersector::add(Polygon2 *polygon2) {
    Path path = polygon2->getPath();

    // FIXME: ptSubject o ptClip?
    cplr->AddPath(path, ptSubject, true);
}

Intersector::~Intersector() {
    delete(cplr);
}

Intersector::Intersector(Polygon3 *polygon3) {
    this->polygon3 = polygon3;
    this->cplr = new Clipper;
    cplr->Clear();
}
