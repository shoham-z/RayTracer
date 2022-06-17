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

    /**
     * Calculates a point on the line of the ray at a given distance from the starting point
     *
     * @param t the distance from the starting point
     * @return the point on the line of the ray
     */
    Point getPoint(double t);

    /**
     * Getter for the ray's starting Point
     *
     * @return the start Point
     */
    Point getStart();

    /**
     * Getter for the ray's direction Vector
     *
     * @return the direction vector
     */
    Vector getDirection();


    bool operator==(Ray &ray);

    friend std::ostream &operator<<(std::ostream &os, Ray &ray);
};


#endif //RAYTRACER_RAY_H
