//
// Created by shoham on 6/20/22.
//

#include "geometries/Triangle.h"

Triangle::Triangle(Point p1, Point p2, Point p3) : Plane(p1, p2, p3) {
Plane(p1,p2,p3);
this->vertices[0] = p1;
this->vertices[1] = p2;
this->vertices[2] = p3;
}

std::list<GeoPoint> Triangle::findGeoIntersectionsHelper(Ray ray, double maxDistance) {
    std::list<GeoPoint> planeIntersection =  Plane::findGeoIntersectionsHelper(ray, maxDistance);
    if(planeIntersection.empty()) return planeIntersection;
    Point p0 = ray.getStart();
    Vector v = ray.getDirection();
    std::list<GeoPoint> intersection;
    Vector v1 = vertices[0].subtract(p0);
    Vector v2 = vertices[1].subtract(p0);
    Vector n1 = v1.crossProduct(v2).normalize();
    double vn1 = Util::alignZero(v.dotProduct(n1));
    if (vn1 == 0) return intersection;

    Vector v3 = vertices[2].subtract(p0);
    Vector n2 = v2.crossProduct(v3).normalize();
    double vn2 = Util::alignZero(v.dotProduct(n2));
    if (vn1 * vn2 <= 0) return intersection;

    Vector n3 = v3.crossProduct(v1).normalize();
    double vn3 = Util::alignZero(v.dotProduct(n3));
    if (vn1 * vn3 <= 0) return intersection;


    Point intersect = planeIntersection.front().point;

    intersection.emplace_back(GeoPoint(this, intersect));
    return intersection;
}

Triangle Triangle::setMaterial(Material material) {
    this->material = material;
    return *this;
}

Triangle Triangle::setEmission(Color emission) {
    this->emission = emission;
    return *this;
}

