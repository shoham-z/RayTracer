//
// Created by shoham on 6/16/22.
//
#include "Geometry.h"
#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H


class Sphere : Geometry {
double radius;
Point center;
public:
    Sphere(double radius, Point center);


    Vector getNormal(Point point) override;

    std::list<Point> findIntersections(Ray ray) override;
};


#endif //RAYTRACER_SPHERE_H
