//
// Created by shoham on 6/16/22.
//
#include <iostream>
#include "Vector.h"

#ifndef RAYTRACER_POINT_H
#define RAYTRACER_POINT_H

class Point {
    double x, y, z;
public:
    static Point ZERO() { return {0, 0, 0}; };

    static Point ONE() { return {1, 1, 1}; };

    Point(double x, double y, double z);

    Point add(Vector other);

    Vector subtract(Point point);

    double distance(Point other);

    double getX();

    double getY();

    double getZ();

    bool operator==(Point &point);

    friend std::ostream &operator<<(std::ostream &os, Point &point);
};


#endif //RAYTRACER_POINT_H
