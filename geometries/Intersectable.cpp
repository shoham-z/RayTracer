//
// Created by shoham on 6/16/22.
//
#include "geometries/Intersectable.h"


std::list<GeoPoint> Intersectable::findGeoIntersections(Ray ray) {
    return findGeoIntersectionsHelper(ray, std::numeric_limits<double>::max());
}


std::list<Point> Intersectable::findIntersections(Ray ray) {
    std::list<GeoPoint> geoIntersections = this->findGeoIntersections(ray);
    std::list<Point> intersections;
    std::for_each(geoIntersections.begin(), geoIntersections.end(),
                  [&intersections](GeoPoint geoPoint) {
                      if (std::find(intersections.begin(), intersections.end(), geoPoint.point) ==
                          intersections.end()) {
                          intersections.push_back(geoPoint.point);
                      }
                  });
    return intersections;
}

std::list<GeoPoint> Intersectable::findGeoIntersections(Ray ray, double maxDistance) {
    return findGeoIntersectionsHelper(ray, maxDistance);
}






