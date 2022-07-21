//
// Created by shoham on 7/20/22.
//

#ifndef RAYTRACER_ELLIPSOID_H
#define RAYTRACER_ELLIPSOID_H


#include "primitives/Point.h"
#include "geometries/Geometry.h"

class Ellipsoid : public Geometry{
    Point center;
    double r1, r2, r3;
public:
    Ellipsoid(Point p, double radius1, double radius2, double radius3);

    Vector getNormal(Point p) override;

    std::list<GeoPoint> findGeoIntersectionsHelper(Ray ray, double maxDistance) override;

    Ellipsoid setMaterial(Material mat);
    Ellipsoid setEmission(Color color);

};


#endif //RAYTRACER_ELLIPSOID_H
