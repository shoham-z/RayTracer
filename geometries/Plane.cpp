//
// Created by shoham on 6/20/22.
//
#include "Util.h"
#include "Plane.h"

std::list <GeoPoint> Plane::findGeoIntersectionsHelper(Ray ray) {
    std::list <GeoPoint> intersection;
    double denominator = this->normal.dotProduct(ray.getDirection());
    if (Util::isZero(denominator))
        return intersection;

    Vector u = Vector(0,0,0);

        u = this->point.subtract(ray.getStart());
    if (u.isZero()) {
        return intersection;
    }

    double t = Util::alignZero(this->normal.dotProduct(u) / denominator);
    if (t > 0) intersection.emplace_back(this, ray.getPoint(t));
    return intersection;
}

Plane::Plane(Point point, Vector vector) : point(point) , normal(vector.normalize()) {

}

Plane::Plane(Point p1, Point p2, Point p3) :point(p1), normal(p1.subtract(p2).crossProduct(p1.subtract(p3)).normalize()){
}

Point Plane::getPoint() {
    return this->point;
}

Vector Plane::getNormal() {
    return this->normal;
}

Vector Plane::getNormal(Point point) {
    return this->normal;
}
