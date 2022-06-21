//
// Created by shoham on 6/16/22.
//

#include "primitives/Vector.h"

Vector::Vector(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector Vector::add(Vector other) const {
    return {this->x + other.x, this->y + other.y, this->z + other.z};
}

Vector Vector::subtract(Vector other) const {
    return {this->x - other.x, this->y - other.y, this->z - other.z};
}

double Vector::dotProduct(Vector other) const {
    return this->x * other.x + this->y * other.y + this->z * other.z;
}

Vector Vector::crossProduct(Vector other) const {
    return {this->y * other.z - this->z * other.y, this->z * other.x - this->x * other.z,
            this->x * other.y - this->y * other.x};
}

Vector Vector::normalize() const {
    return this->scale(1 / this->length());
}

Vector Vector::scale(double scalar) const {
    return {this->x * scalar, this->y * scalar, this->z * scalar};
}

double Vector::length() const {
    return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}

double Vector::lengthSquared() const {
    return this->x * this->x + this->y * this->y + this->z * this->z;
}

bool Vector::operator==(Vector &vector) const {
    return this->x == vector.x && this->y == vector.y && this->z == vector.z;
}

std::ostream &operator<<(std::ostream &os, Vector &vector) {
    os << "vector(" << vector.x << ", " << vector.y << ", " << vector.z << ")";
    return os;
}

bool Vector::isZero() {
    Vector zero = Vector::ZERO();
    return this->operator==(zero);
}

