//
// Created by shoham on 7/17/22.
//

#ifndef RAYTRACER_STREETLAMP_H
#define RAYTRACER_STREETLAMP_H


#include "geometries/Sphere.h"
#include "lights/PointLight.h"
#include "geometries/Geometries.h"
#include <memory>

class StreetLamp {
public:
    Geometries geometries;
    PointLight light;

    /**
     * Constructor for street lamp
     * @param point Position of the base
     * @param height Height of the light
     * @param color Color of the light
     * @param up Up direction
     * @param radius Radius of poles
     */
    StreetLamp(Point point, double height, Color color, Vector up, double radius);


};


#endif //RAYTRACER_STREETLAMP_H
