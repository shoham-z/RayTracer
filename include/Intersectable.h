//
// Created by shoham on 6/16/22.
//
#include <list>
#include "Ray.h"
#include "Util.h"
#include "GeoPoint.h"
#include <algorithm>


#ifndef RAYTRACER_INTERSECTABLE_H
#define RAYTRACER_INTERSECTABLE_H


class Intersectable {
public:

    std::list<Point> findIntersections(Ray ray);

    virtual std::list<GeoPoint> findGeoIntersectionsHelper(Ray ray) = 0;


    std::list<GeoPoint> findGeoIntersections(Ray ray);
};

#endif //RAYTRACER_INTERSECTABLE_H
