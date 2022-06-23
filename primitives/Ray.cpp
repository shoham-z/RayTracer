//
// Created by shoham on 6/16/22.
//

#include "primitives/Ray.h"

Ray::Ray(Point start, Vector dir) : dir(dir.normalize()), start(start) {
}

Ray::Ray(Point head, Vector direction, Vector normal) :
        start(Point()),
        dir(direction.normalize()) {
    this->start = head.add(normal.scale(normal.dotProduct(direction) > 0 ? this->DELTA : -this->DELTA));
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

Point Ray::findClosestPoint(std::list<Point> points) {

    Point point = Point(0, 0, 0);
    double distance = std::numeric_limits<double>::max();
    for (Point geoPoint: points) {
        double d = this->start.distance(point);
        if (d < distance) {
            distance = d;
            point = geoPoint;
        }
    }
    return point;

}

GeoPoint Ray::findClosestGeoPoint(std::list<GeoPoint> geoPoints) {
    int index = -1;
    GeoPoint goodGeoPoint;
    double distance = std::numeric_limits<double>::max();
    for (GeoPoint geoPoint:
            geoPoints) {
        if (geoPoint.point.subtract(this->start).dotProduct(this->dir) > 0) {
            double d = this->start.distance(geoPoint.point);
            if (d < distance) {
                distance = d;
                goodGeoPoint = geoPoint;
            }
        }
    }
    return goodGeoPoint;
}

