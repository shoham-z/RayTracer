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
