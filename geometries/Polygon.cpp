//
// Created by shoham on 7/17/22.
//

#include "geometries/Polygon.h"

#include <utility>
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
    Vector n = Vector::ZERO();
    for (int i = 1; i <= this->edges.size(); ++i) {
        Vector t = this->edges[i%edges.size()].subtract(this->edges[i-1])
                .crossProduct(this->edges[i-1].subtract(p));
        if(n.isZero()) n = t;
        else if (n.dotProduct(t)<=0)
            return intersections;
    }
    intersections.emplace_back(this, p);
    return intersections;
}

Polygon::Polygon(std::vector<Point> points) {
    if (points.size()<3){
        std::cout<<"Invalid Polygon Vertices!"<<std::endl;
        exit(-1);
    }
    this->edges = std::move(points);
    this->emission=Color::red();
}

Polygon Polygon::setMaterial(Material material) {
    this->material = material;
    return *this;
}

Polygon Polygon::setEmission(Color emission) {
    this->emission = emission;
    return *this;
}
