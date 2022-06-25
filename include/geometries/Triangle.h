//
// Created by shoham on 6/20/22.
//
#include "Plane.h"

#ifndef RAYTRACER_TRIANGLE_H
#define RAYTRACER_TRIANGLE_H


class Triangle : public Plane {
    Point vertices[3];
public:
    Triangle(Point p1, Point p2, Point p3);

    std::list<GeoPoint> findGeoIntersectionsHelper(Ray ray, double maxDistance) override;

    Triangle setMaterial(Material material);

    Triangle setEmission(Color emission);

};


#endif //RAYTRACER_TRIANGLE_H
