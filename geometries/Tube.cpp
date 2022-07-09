//
// Created by shoham on 7/9/22.
//

#include "geometries/Tube.h"


Tube::Tube(Ray axis, double radius) : axis(axis) {
    this->radius = radius;
}

Ray Tube::getDirection() {
    return this->axis;
}

double Tube::getRadius() {
    return this->radius;
}

Vector Tube::getNormal(Point point) {
    Vector dir = this->axis.getDirection();
    Point p0 = this->axis.getStart();
    double t = dir.dotProduct(point.subtract(p0));
    Point o = Util::isZero(t) ? p0 : p0.add(dir.scale(t));
    return point.subtract(o).normalize();
}

std::list<GeoPoint> Tube::findGeoIntersectionsHelper(Ray ray, double maxDistance) {
    Point rayStart = ray.getStart();
    Vector rayDir = ray.getDirection();
    Point tubeStart = this->axis.getStart();
    Vector tubeDir = this->axis.getDirection();
    Vector K = Vector(0, 0, 0);

    std::list<GeoPoint> intersections;

    K = rayDir.crossProduct(tubeDir);
    if (K.isZero()) return intersections;
    Vector E = Vector(0, 0, 0);
    E = rayStart.subtract(tubeStart).crossProduct(tubeDir);
    if (K.isZero()) {

        intersections.emplace_back(this, rayStart.add(rayDir.scale(getRadius() / K.length())));
        return intersections;
    }

    double a = K.lengthSquared();
    double b = 2 * K.dotProduct(E);
    double c = E.lengthSquared() - this->radius * this->radius;
    double delta = Util::alignZero(b * b - 4 * a * c);
    if (delta < 0)
        return intersections;
    if (delta == 0) {
        double t = Util::alignZero((-b) / (2 * a));
        if (t <= 0)
            return intersections;
        intersections.emplace_back(this, t == 0 ? rayStart : rayStart.add(rayDir.scale(t)));
        return intersections;

    }
    double sDelta = sqrt(delta);
    double t1 = Util::alignZero((-b + sDelta) / (2 * a));
    double t2 = Util::alignZero((-b - sDelta) / (2 * a));
    if (t1 <= 0) return intersections;
    if (t2 > 0 && Util::alignZero(t2 - maxDistance) <= 0)
        intersections.emplace_back(GeoPoint(this, rayStart.add(rayDir.scale(t2))));
    if (t1 - maxDistance <= 0)
        intersections.emplace_back(GeoPoint(this, t1 == 0 ? rayStart : rayStart.add(rayDir.scale(t1))));
    return intersections;
}

Tube Tube::setEmission(Color emission) {
    this->emission = emission;
    return *this;
}

Tube Tube::setMaterial(Material material) {
    this->material = material;
    return *this;
}
