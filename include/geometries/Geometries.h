//
// Created by shoham on 6/17/22.
//
#include "Intersectable.h"
#include "Geometry.h"

#ifndef RAYTRACER_GEOMETRIES_H
#define RAYTRACER_GEOMETRIES_H


class Geometries : public Intersectable {
    std::list<std::shared_ptr<Geometry>> geometries;


public:

    void add(std::list<std::shared_ptr<Geometry>> newGeometries);

    void add(const std::shared_ptr<Geometry>& newGeometry);

    std::list<GeoPoint> findGeoIntersectionsHelper(Ray ray, double maxDistance) override;

    explicit Geometries(std::list<std::shared_ptr<Geometry>> newGeometries);

    Geometries();
};


#endif //RAYTRACER_GEOMETRIES_H
