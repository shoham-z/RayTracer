//
// Created by shoham on 6/16/22.
//

#include "geometries/Sphere.h"

Sphere::Sphere(Point center, double radius) : center(center) {
    this->radius = radius;
}

Vector Sphere::getNormal(Point point) {
    return point.subtract(this->center).normalize();
}

std::list<GeoPoint> Sphere::findGeoIntersectionsHelper(Ray ray, double maxDistance) {
    std::list<GeoPoint> intersections;
    Vector u = Vector(0, 0, 0);
    if (ray.getStart() == this->center) {
        intersections.emplace_back(GeoPoint(this, ray.getPoint(this->radius)));
        return intersections;
    } else
        u = this->center.subtract(ray.getStart());

    double tm = ray.getDirection().dotProduct(u);
    double d2 = u.lengthSquared() - (tm * tm);
    if (d2 < 0) return intersections;

    double th2 = Util::alignZero(this->radius * this->radius - d2);
    if (th2 > 0) {

        double th = Util::alignZero(sqrt(th2));

        double t1 = Util::alignZero(tm - th);
        if (Util::alignZero(t1 - maxDistance) > 0) return intersections;
        double t2 = Util::alignZero(tm + th);
        if (t2 <= 0) return intersections;
        if (Util::alignZero(t2 - maxDistance) >= 0)
            t1 <= 0 ? intersections.emplace_back(GeoPoint(this, ray.getPoint(t2))) : intersections.emplace_back(
                    GeoPoint(this, ray.getPoint(t1)));

        if (t1 <= 0) intersections.emplace_back(GeoPoint(this, ray.getPoint(t2)));
        else {
            intersections.emplace_back(GeoPoint(this, ray.getPoint(t1)));
            intersections.emplace_back(GeoPoint(this, ray.getPoint(t2)));
        }
    }
    return intersections;
}

Sphere Sphere::setEmission(Color emission) {
    this->emission = emission;
    return *this;
}

Sphere Sphere::setMaterial(Material material) {
    this->material = material;
    return *this;
}


