//
// Created by shoham on 6/16/22.
//
#include <iostream>
#include <cmath>


#ifndef RAYTRACER_VECTOR_H
#define RAYTRACER_VECTOR_H


class Vector {
public:
    double x,y,z;

    Vector(double x, double y, double z);

    Vector add(Vector other) const;
    Vector subtract(Vector other) const;
    double dotProduct(Vector other);
    Vector crossProduct(Vector other);
    Vector normalize();
    Vector scale(double scalar);
    double length();

    bool operator==(Vector &vector);
    friend std::ostream &operator<<(std::ostream &os, Vector &vector);

};


#endif //RAYTRACER_VECTOR_H
