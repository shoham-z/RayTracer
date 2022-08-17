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
    std::vector<Point> edges;
public:
    Polygon(std::vector<Point> points);//change this to array and size OR a list

    Vector getNormal(Point point) override;

    std::list<GeoPoint> findGeoIntersectionsHelper(Ray ray, double maxDistance) override;

    Polygon setMaterial(Material material);

    Polygon setEmission(Color emission);

};


#endif //RAYTRACER_POLYGON_H
