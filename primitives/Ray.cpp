//
// Created by shoham on 6/16/22.
//

#include "Ray.h"

Ray::Ray(Point start, Vector dir) : dir(dir), start(start) {
}

bool Ray::operator==(Ray &ray) {
    return this->dir == ray.dir && this->start == ray.start;
}

std::ostream &operator<<(std::ostream &os, Ray &ray) {
    os << "ray(" << ray.start << ", " << ray.dir << ")";
    return os;
}

Point Ray::getPoint(double t) {
    return this->start.add(this->dir.scale(t));
}

Point Ray::getStart() {
    return this->start;
}

Vector Ray::getDirection() {
    return this->dir;
}
