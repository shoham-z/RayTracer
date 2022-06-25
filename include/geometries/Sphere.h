//
// Created by shoham on 6/16/22.
//
#include "Geometry.h"

#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H


class Sphere : public Geometry {
    double radius;
    Point center;
public:
    Sphere(Point center, double radius);


    Vector getNormal(Point point) override;

    std::list<GeoPoint> findGeoIntersectionsHelper(Ray ray, double maxDistance);

    Sphere setEmission(Color emission);

    Sphere setMaterial(Material material);

};


#endif //RAYTRACER_SPHERE_H
