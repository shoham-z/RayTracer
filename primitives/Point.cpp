//
// Created by shoham on 6/16/22.
//

#include "primitives/Point.h"


Point::Point(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Point Point::add(Vector other) const {
    return {this->x + other.x, this->y + other.y, this->z + other.z};
}

double Point::distance(Point other) const {
    return sqrt((this->x - other.x) * (this->x - other.x) + (this->y - other.y) * (this->y - other.y) +
                (this->z - other.z) * (this->z - other.z));
}

bool Point::operator==(Point point) const {
    return this->x == point.x && this->y == point.y && this->z == point.z;
}

std::ostream &operator<<(std::ostream &os, Point &point) {
    os << "point(" << point.x << ", " << point.y << ", " << point.z << ")";
    return os;
}

Vector Point::subtract(Point point) const {
    return Vector(this->x - point.x, this->y - point.y, this->z - point.z);
}

double Point::getX() const {
    return this->x;
}

double Point::getY() const {
    return this->y;
}

double Point::getZ() const {
    return this->z;
}

Point::Point() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

double Point::distanceSquared(Point other) const {
    return (this->x - other.x) * (this->x - other.x) + (this->y - other.y) * (this->y - other.y) +
           (this->z - other.z) * (this->z - other.z);
}

Point::Point(double x) {
this->x = x;
    this->y = x;
    this->z = x;
}
