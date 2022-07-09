//
// Created by shoham on 7/9/22.
//

#ifndef RAYTRACER_TUBE_H
#define RAYTRACER_TUBE_H


#include "primitives/Ray.h"

class Tube : public Geometry {
    Ray axis;
    double radius;

public:
    Tube(Ray axis, double radius);

    Ray getDirection();

    double getRadius();

    Vector getNormal(Point point) override;

    std::list<GeoPoint> findGeoIntersectionsHelper(Ray ray, double maxDistance) override;


    Tube setEmission(Color emission);

    Tube setMaterial(Material material);
};


#endif //RAYTRACER_TUBE_H
