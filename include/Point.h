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
    Point(double x,double y,double z);
    Point add(Vector other);
    Vector subtract(Point point);
    double distance(Point other);

    bool operator==(Point &point);
    friend std::ostream &operator<<(std::ostream &os, Point &point);
};


#endif //RAYTRACER_POINT_H
