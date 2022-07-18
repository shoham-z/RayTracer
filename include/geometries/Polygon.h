//
// Created by shoham on 7/17/22.
//

#ifndef RAYTRACER_POLYGON_H
#define RAYTRACER_POLYGON_H


#include <list>
#include "primitives/Vector.h"
#include "primitives/Point.h"
#include "GeoPoint.h"

class Polygon : public Geometry {
Point edges[4];
public:
    Polygon(Point p1,Point p2,Point p3,Point p4);

    Vector getNormal(Point point) override;

    std::list<GeoPoint> findGeoIntersectionsHelper(Ray ray, double maxDistance) override;

    Polygon setMaterial(Material material);

    Polygon setEmission(Color emission);

};


#endif //RAYTRACER_POLYGON_H
