//
// Created by shoham on 6/16/22.
//
#include "Vector.h"
#include "Point.h"
#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H


class Ray {
Point start;
Vector dir;
public:
    Ray(Point start, Vector dir);

    bool operator==(Ray &ray);
    friend std::ostream &operator<<(std::ostream &os, Ray &ray);
};


#endif //RAYTRACER_RAY_H
