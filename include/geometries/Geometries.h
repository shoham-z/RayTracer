//
// Created by shoham on 6/17/22.
//
#include "Intersectable.h"
#include "Geometry.h"
#include <memory>


#ifndef RAYTRACER_GEOMETRIES_H
#define RAYTRACER_GEOMETRIES_H


class Geometries : public Intersectable {
public:
    std::list<std::shared_ptr<Geometry>> geometries;

    void add(std::list<std::shared_ptr<Geometry>> newGeometries);

    void addShared(const std::shared_ptr<Geometry>& newGeometry);

    void add(const Geometries& otherGeometries);

    std::list<GeoPoint> findGeoIntersectionsHelper(Ray ray, double maxDistance) override;

    explicit Geometries(std::list<std::shared_ptr<Geometry>> newGeometries);

    Geometries();
};


#endif //RAYTRACER_GEOMETRIES_H
