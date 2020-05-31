//
// Created by Braulio Lobo on 29-05-20.
//

#include "Line3.h"

Line3::Line3(Vector3 director, Vector3 point) {
    this->director = director;
    this->point = point;
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
