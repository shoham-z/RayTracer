//
// Created by shoham on 7/17/22.
//

#ifndef RAYTRACER_PYRAMID_H
#define RAYTRACER_PYRAMID_H


#include "primitives/Point.h"
#include "geometries/Geometries.h"
#include "geometries/Polygon.h"
#include "geometries/Triangle.h"

class Pyramid {
public:
 Geometries pyramid;

    /**
     * Constructor for Pyramid
     * @param bottomCenter Bottom center of the pyramid
     * @param height Height of the pyramid
     * @param width Width of the pyramid
     * @param vTo To direction of the pyramid
     * @param vUp Up direction of the pyramid
     * @param color Color of the pyramid
     * @param material Material of the pyramid
     */
 Pyramid(Point bottomCenter, double height, double width, Vector vTo, Vector vUp, Color color, Material material);

    };


#endif //RAYTRACER_PYRAMID_H
