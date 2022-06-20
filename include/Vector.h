//
// Created by shoham on 6/16/22.
//
#include <iostream>
#include <cmath>


#ifndef RAYTRACER_VECTOR_H
#define RAYTRACER_VECTOR_H


class Vector {
public:
    double x, y, z;

    Vector(double x, double y, double z);

    static Vector ZERO() {return {0,0,0};};

    bool isZero();
    /**
     * Sum two vectors triads into a new triad vector by adding the two points
     * that are constructing the vectors
     *
     * @param other the point of the second vector for adding it to the first vector
     * @return new vector, result of add
     */
    Vector add(Vector other) const;

    /**
     * Subtracts two vectors triads into a new triad vector by subtracting the two points
     * that are constructing the vectors
     *
     * @param other the point of the second vector for subtracting it to the first vector
     * @return new vector, result of subtract
     */
    Vector subtract(Vector other) const;

    /**
     * Product two vectors into a scalar where each couple of
     * numbers are multiplied, and then added together.
     *
     * @param other the second vector for dot-product
     * @return scalar, result of dot-product
     */
    double dotProduct(Vector other) const;

    /**
     * Product two vectors into a new vector, witch is a vector that is perpendicular to both vectors
     * and thus normal to the plane containing them.
     *
     * @param other the second vector for cross-product
     * @return vector, result of cross-product
     */
    Vector crossProduct(Vector other) const;

    /**
     * for normalizing vectors, in the same direction as the original vector.
     *
     * @return a normalized vector, in the same direction as the original vector.
     */
    Vector normalize() const;

    /**
     * Scale (multiply) point of vector by a number into a new vector where each
     * number of the point is multiplied by the number
     *
     * @param scalar the number for scaling
     * @return new vector, result of scale
     */
    Vector scale(double scalar) const;

    /**
     * calculates the length of the vector.
     *
     * @return number, the length of the vector.
     */
    double length() const;

    /**
     * calculates the length squared of the vector.
     *
     * @return number, the length squared of the vector.
     */
    double lengthSquared() const;

    bool operator==(Vector &vector) const;

    friend std::ostream &operator<<(std::ostream &os, Vector &vector);

};


#endif //RAYTRACER_VECTOR_H
