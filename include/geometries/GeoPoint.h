//
// Created by shoham on 6/19/22.
//

#ifndef RAYTRACER_GEOPOINT_H
#define RAYTRACER_GEOPOINT_H


#include "primitives/Point.h"
#include "Geometry.h"

class GeoPoint {
public:
    Point point;
    Geometry* geometry{};
    GeoPoint(Geometry *geometry, Point point);
    GeoPoint();


    bool operator==(GeoPoint &other);
    bool operator!();

};



#endif //RAYTRACER_GEOPOINT_H
