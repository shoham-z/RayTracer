//
// Created by shoham on 6/16/22.
//
#include <iostream>
#include "Vector.h"

#ifndef RAYTRACER_POINT_H
#define RAYTRACER_POINT_H

class Point {
public:
    double x, y, z;
    Point();

    static Point ZERO() { return {0, 0, 0}; };

    static Point ONE() { return {1, 1, 1}; };

    Point(double x, double y, double z);
    Point(double x);

    Point add(Vector other) const;

    Vector subtract(Point point) const;

    double distance(Point other) const;

    double distanceSquared(Point other) const;

    double getX() const;

    double getY() const;

    double getZ() const;

    bool operator==(Point point) const;

    friend std::ostream &operator<<(std::ostream &os, Point &point);
};


#endif //RAYTRACER_POINT_H
