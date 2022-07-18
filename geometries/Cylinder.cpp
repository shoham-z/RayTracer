//
// Created by shoham on 7/18/22.
//

#include "geometries/Cylinder.h"

Cylinder Cylinder::setMaterial(Material material) {
    this->material = material;
    return *this;
}

Cylinder Cylinder::setEmission(Color color) {
    this->emission = color;
    return *this;}

std::list<GeoPoint> Cylinder::findGeoIntersectionsHelper(Ray ray, double maxDistance) {
    std::list <Point> points;

    Point upPoint = this->getDirection().getStart().add(this->getDirection().getDirection().scale(height));
    std::list <GeoPoint> pointsT = Tube::findGeoIntersectionsHelper(ray, maxDistance);

    if (!pointsT.empty())
        for (GeoPoint geopoint: pointsT) {
            double A = geopoint.point.distanceSquared(this->getDirection().getStart());
            double R = this->getRadius() * this->getRadius();
            Vector v = this->getDirection().getStart().subtract(geopoint.point);
            if (sqrt(A - R) <= height && v.dotProduct(this->getDirection().getDirection()) <= 0)
                points.push_back(geopoint.point);
        }

    Plane p1 = Plane(this->getDirection().getStart(), this->getDirection().getDirection().scale(-1));
    Plane p2 = Plane(upPoint, this->getDirection().getDirection());

    std::list <Point> point1 = p1.findIntersections(ray);
    std::list<Point> point2 = p2.findIntersections(ray);

    if (!point1.empty() &&
        point1.front().distance(this->getDirection().getStart()) - this->getRadius() <= 0)
        points.push_back(point1.front());
    if (!point2.empty() && point2.front().distance(upPoint) - this->getRadius() <= 0)
        points.push_back(point2.front());

    std::list<GeoPoint> intersections;
    if (points.empty()) {
        return intersections;
    }
    for (Point point: points) {
        intersections.emplace_back(this, point);
    }
    return intersections;
}

Vector Cylinder::getNormal(Point point) {
    Vector dir = this->getDirection().getDirection();
    Point p0 = this->getDirection().getStart();
    if (point ==p0) {
        return dir.scale(-1);
    }
    double t = dir.dotProduct(point.subtract(p0));
    if (t==0) {
        return dir.scale(-1);
    }
    if (t == this->height) {
        return dir;
    }
    Point o = p0.add(dir.scale(t));
    Vector normal = point.subtract(o);
    return normal.normalize();
}
