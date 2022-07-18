//
// Created by shoham on 7/17/22.
//

#include "geometries/Polygon.h"
#include "primitives/Vector.h"
#include "geometries/GeoPoint.h"
#include "geometries/Plane.h"

Vector Polygon::getNormal(Point point) {
    return this->edges[1].subtract(this->edges[0]).crossProduct(this->edges[2].subtract(this->edges[0]));
}

std::list<GeoPoint> Polygon::findGeoIntersectionsHelper(Ray ray, double maxDistance) {
    Plane plane = Plane(this->edges[0], this->edges[1], this->edges[2]);
    Point p = plane.findGeoIntersectionsHelper(ray, maxDistance).front().point;
    std::list<GeoPoint> intersections;
    Vector n1 = this->edges[1].subtract(this->edges[0])
            .crossProduct(this->edges[0].subtract(p));
    Vector n2 = this->edges[2].subtract(this->edges[1])
            .crossProduct(this->edges[1].subtract(p));
    if (n1.dotProduct(n2)<=0) return intersections;

    Vector n3 = this->edges[3].subtract(this->edges[2])
            .crossProduct(this->edges[2].subtract(p));
    if (n1.dotProduct(n3)<=0) return intersections;

    Vector n4 = this->edges[0].subtract(this->edges[3])
            .crossProduct(this->edges[3].subtract(p));
    if (n1.dotProduct(n4)<=0) return intersections;
    intersections.emplace_back(this, p);
    return intersections;
}

Polygon::Polygon(Point p1, Point p2, Point p3, Point p4) {
    this->edges[0] = p1;
    this->edges[1] = p2;
    this->edges[2] = p3;
    this->edges[3] = p4;
}

Polygon Polygon::setMaterial(Material material) {
    this->material = material;
    return *this;
}

Polygon Polygon::setEmission(Color emission) {
    this->emission = emission;
    return *this;
}
