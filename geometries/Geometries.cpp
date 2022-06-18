//
// Created by shoham on 6/17/22.
//

#include "Geometries.h"


Geometries::Geometries(std::list<Geometry*> newGeometries) {
    this->geometries.splice(this->geometries.end(), newGeometries);
}

void Geometries::add(std::list<Geometry*> newGeometries) {
    this->geometries.splice(this->geometries.end(), newGeometries);
}

std::list<Point> Geometries::findIntersections(Ray ray) {
    std::list<Point> intersections;
    std::list<Geometry>::iterator it;

    std::for_each(this->geometries.begin(), this->geometries.end(),
                  [&ray, &intersections](Geometry* geometry) {
                        std::list<Point> tmp = geometry->findIntersections(ray);
                      intersections.splice(intersections.end(), tmp);
                  });
    return intersections;
}

Geometries::Geometries() {

}

void Geometries::add(Geometry* newGeometry) {
this->geometries.push_back(newGeometry);
}
