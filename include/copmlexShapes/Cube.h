//
// Created by shoham on 7/17/22.
//

#ifndef RAYTRACER_CUBE_H
#define RAYTRACER_CUBE_H


#include "geometries/Geometries.h"
#include "geometries/Polygon.h"

class Cube {
public:
Geometries cube;

    /**
     * Constructor for Cube
     * @param center Center point of the Cube
     * @param length Length of the Cube
     * @param vUp Up direction of the Cube
     * @param vRight Right direction of the Cube
     * @param color Color of the Cube
     * @param material Material of the Cube
     */
Cube(Point center, double length, Vector vUp, Vector vRight, Color color, Material material);


    /**
     * Constructs a two-dimensional rectangle
     *
     * @param center Center point of the rectangle
     * @param vRight Right direction of the rectangle
     * @param vUp    Up direction of the rectangle
     * @param height Height of the rectangle
     * @param width  Width of the rectangle
     * @return The new rectangle
     */
    Polygon constructRectangle(Point center, Vector vRight, Vector vUp, double height, double width);
};


#endif //RAYTRACER_CUBE_H
