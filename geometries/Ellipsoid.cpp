//
// Created by shoham on 7/20/22.
//

#include "geometries/Ellipsoid.h"
#include "primitives/Point.h"

Ellipsoid::Ellipsoid(Point p, double radius1, double radius2, double radius3) : center(p) {
    this->r1 = radius1;
    this->r2 = radius2;
    this->r3 = radius3;
}

Vector Ellipsoid::getNormal(Point p) {
    return Vector(
            (p.x-this->center.x) / (this->r1*this->r1)
            ,(p.y-this->center.y) / (this->r2*this->r2)
            ,(p.z-this->center.z) / (this->r3*this->r3)
    ).normalize();
    //return Vector( this->r1*p.x + this->center.x ,  this->r2*p.y + this->center.y,  this->r3*p.z + this->center.z);//.normalize();
}

std::list<GeoPoint> Ellipsoid::findGeoIntersectionsHelper(Ray ray, double maxDistance) {
    std::list<GeoPoint> intersection;
    double rayDirX = ray.dir.x / this->r1;
    double rayDirY = ray.dir.y / this->r2;
    double rayDirZ = ray.dir.z / this->r3;
    double rayOrgX = ray.start.x / this->r1;
    double rayOrgY = ray.start.y / this->r2;
    double rayOrgZ = ray.start.z / this->r3;
    double thisCenterX = this->center.x / this->r1;
    double thisCenterY = this->center.y / this->r2;
    double thisCenterZ = this->center.z / this->r3;
    double a = rayDirX * rayDirX + rayDirY * rayDirY + rayDirZ * rayDirZ;
    double b = 2 * ((rayDirX * rayOrgX * rayDirY * rayOrgY + rayDirZ * rayOrgZ) -
                    (rayDirX * thisCenterX + rayDirY * thisCenterY + rayDirZ * thisCenterZ));
    double c = ((rayOrgX * rayOrgX + rayOrgY * rayOrgY + rayOrgZ * rayOrgZ) +
                (thisCenterX * thisCenterX + thisCenterY * thisCenterY + thisCenterZ * thisCenterZ) -
                (thisCenterX * rayOrgX + thisCenterY * rayOrgY + thisCenterZ * rayOrgZ) - 1);
    double desc2 = b * b - 4 * a * c;
    if (desc2 == 0) {
        double t = -b / (2 * a);
        intersection.emplace_back(this, ray.getPoint(t));
    }
    if (desc2 > 0) {
        double desc = sqrt(desc2);
        double t1 = (-b + desc) / (2 * a);
        double t2 = (-b - desc) / (2 * a);
        intersection.emplace_back(this, ray.getPoint(t1));
        intersection.emplace_back(this, ray.getPoint(t2));
    }
    return intersection;
}

Ellipsoid Ellipsoid::setMaterial(Material mat) {
    this->material = mat;
    return *this;
}

Ellipsoid Ellipsoid::setEmission(Color color) {
    this->emission = color;
    return *this;
}
