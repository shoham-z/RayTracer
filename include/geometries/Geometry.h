//
// Created by shoham on 6/16/22.
//
#include "primitives/Vector.h"
#include "primitives/Point.h"
#include "Intersectable.h"
#include "primitives/Color.h"
#include "primitives/Material.h"

#ifndef RAYTRACER_GEOMETRY_H
#define RAYTRACER_GEOMETRY_H


class Geometry: public Intersectable {
    Color emission;
    Material material = Material();
public:
    virtual Vector getNormal(Point point) = 0;
    Material getMaterial();
    Geometry* setMaterial(Material material);
    Color getEmission();
    Geometry* setEmission(Color emission);
};


#endif //RAYTRACER_GEOMETRY_H
