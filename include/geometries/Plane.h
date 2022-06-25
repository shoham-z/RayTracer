//
// Created by shoham on 6/20/22.
//
#include "Geometry.h"

#ifndef RAYTRACER_PLANE_H
#define RAYTRACER_PLANE_H


class Plane : public Geometry {
    const Point point;
    const Vector normal;

public:
    Plane(Point point, Vector vector);

    Plane(Point p1, Point p2, Point p3);

    Point getPoint();

    Vector getNormal();

    Vector getNormal(Point point) override;

    std::list<GeoPoint> findGeoIntersectionsHelper(Ray ray, double maxDistance) override;

    Plane setMaterial(Material material);

    Plane setEmission(Color emission);
};


#endif //RAYTRACER_PLANE_H
