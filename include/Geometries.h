//
// Created by shoham on 6/17/22.
//
#include "Intersectable.h"
#include "Geometry.h"
#ifndef RAYTRACER_GEOMETRIES_H
#define RAYTRACER_GEOMETRIES_H


class Geometries: Intersectable {
    std::list<Geometry*> geometries;


public:

    void add(std::list<Geometry*> newGeometries);
    void add(Geometry* newGeometry);
    std::list<Point> findIntersections(Ray ray) override;
    explicit Geometries(std::list<Geometry*> newGeometries);

    Geometries();
};


#endif //RAYTRACER_GEOMETRIES_H
