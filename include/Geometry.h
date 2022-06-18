//
// Created by shoham on 6/16/22.
//
#include "Vector.h"
#include "Point.h"
#include "Intersectable.h"
#include "Color.h"
#include "Material.h"

#ifndef RAYTRACER_GEOMETRY_H
#define RAYTRACER_GEOMETRY_H


class Geometry: public Intersectable {
    //Color emission;
public:
    virtual Vector getNormal(Point point) = 0;
};


#endif //RAYTRACER_GEOMETRY_H
