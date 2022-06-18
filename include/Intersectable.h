//
// Created by shoham on 6/16/22.
//
#include <list>
#include "Ray.h"
#include "Util.h"
#include <algorithm>


#ifndef RAYTRACER_INTERSECTABLE_H
#define RAYTRACER_INTERSECTABLE_H


class Intersectable {
public:
/**
 * Finds intersections between the ray
 * and the geometry
 *
 * @param ray The ray to intersect with the geometry
 * @return List of intersection points
 */
virtual std::list<Point> findIntersections(Ray ray) = 0;
};


#endif //RAYTRACER_INTERSECTABLE_H
