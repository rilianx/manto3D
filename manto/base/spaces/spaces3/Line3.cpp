//
// Created by Braulio Lobo on 29-05-20.
//

#include <figures/figures3/Figure3.h>
#include "Line3.h"
#include "Plane.h"

Line3::Line3(Vector3 director, Vector3 point) {
    this->director = director;
    this->point = point;
    generateProjections();
}

Vector3 Line3::intersect(const Plane& plane) {
    Vector3 interseccion;

    const Vector3& normal = plane.getNormal();
    const Vector3& p = plane.getPoint();

    // Calculando lambda
    float lambda = (normal.getX()*(p.getX() - point.getX()) +
            normal.getY()*(p.getY() - point.getY()) +
            normal.getZ()*(p.getZ() - point.getZ())) /
            (normal.getX() * director.getX() +
                    normal.getY() * director.getY() +
                    normal.getZ() * director.getZ());

    interseccion = {
            point.getX() + director.getX() * lambda,
            point.getY() + director.getY() * lambda,
            point.getZ() + director.getZ() * lambda
    };

    return interseccion;
}

Line2 *Line3::getProjection(const int i) {
    return &projections[i];
}

void Line3::generateProjections() {
    const int pxy = Figure3::PROJECTION_XY;
    const int pxz = Figure3::PROJECTION_XZ;
    const int pyz = Figure3::PROJECTION_YZ;
    projections[pxy] = Line2({director.getX(), director.getY()},
                             {point.getX(), point.getY()}, true);
    projections[pxz] = Line2({director.getX(), director.getZ()},
                             {point.getX(), point.getZ()}, true);
    projections[pyz] = Line2({director.getY(), director.getZ()},
                             {point.getY(), point.getZ()}, true);
}
