//
// Created by shoham on 6/16/22.
//

#include "Sphere.h"

Sphere::Sphere(double radius, Point center) : center(center) {
    this->radius = radius;
}

Vector Sphere::getNormal(Point point) {
    return point.subtract(this->center).normalize();
}

std::list<Point> Sphere::findIntersections(Ray ray) {
    std::list<Point> intersections;
    Vector u = Vector(0, 0, 0);
    if (ray.getStart() == this->center) {
        intersections.push_back(ray.getPoint(this->radius));
        return intersections;
    } else
        u = this->center.subtract(ray.getStart());

    double tm = ray.getDirection().dotProduct(u);
    double d2 = u.lengthSquared() - tm * tm;
    double th2 = Util::alignZero(this->radius * this->radius - d2);
    if (th2 > 0) {

        double th = Util::alignZero(sqrt(th2));

        double t1 = Util::alignZero(tm - th);
        double t2 = Util::alignZero(tm + th);
        if (t2 > 0)
            t1 <= 0 ? intersections.push_back(ray.getPoint(t2)) : intersections.push_back(ray.getPoint(t1));
        intersections.push_back(ray.getPoint(t2));
    }
    return intersections;
}

