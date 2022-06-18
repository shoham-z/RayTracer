//
// Created by shoham on 6/16/22.
//

#include "Point.h"


Point::Point(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Point Point::add(Vector other) {
    return Point(this->x + other.x,this->y + other.y, this->z + other.z);
}

double Point::distance(Point other) {
    return sqrt((this->x - other.x) * (this->x - other.x) + (this->y - other.y) * (this->y - other.y) +
                (this->z - other.z) * (this->z - other.z));
}

bool Point::operator==(Point &point) {
    return this->x == point.x && this->y == point.y && this->z == point.z;
}

std::ostream &operator<<(std::ostream &os, Point &point) {
    os << "point(" << point.x << ", " << point.y << ", " << point.z << ")";
    return os;
}

Vector Point::subtract(Point point) {
    return Vector(this->x-point.x, this->y-point.y, this->z-point.z);
}

double Point::getX() {
    return this->x;
}

double Point::getY() {
    return this->y;
}

double Point::getZ() {
    return this->z;
}
