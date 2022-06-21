//
// Created by shoham on 6/17/22.
//

#include "geometries/Geometries.h"


Geometries::Geometries(std::list<Geometry*> newGeometries) {
    this->geometries.splice(this->geometries.end(), newGeometries);
}

void Geometries::add(std::list<Geometry*> newGeometries) {
    this->geometries.splice(this->geometries.end(), newGeometries);
}

std::list<GeoPoint> Geometries::findGeoIntersectionsHelper(Ray ray) {
    std::list<GeoPoint> intersections;
    std::list<Geometry>::iterator it;

    std::for_each(this->geometries.begin(), this->geometries.end(),
                  [&ray, &intersections](Geometry* geometry) {
                        std::list<GeoPoint> tmp = geometry->findGeoIntersections(ray);
                      intersections.splice(intersections.end(), tmp);
                  });
    return intersections;
}

Geometries::Geometries() {

}

void Geometries::add(Geometry* newGeometry) {
this->geometries.push_back(newGeometry);
}


