//
// Created by shoham on 6/17/22.
//
#ifndef RAYTRACER_RAYTRACERBASIC_H
#define RAYTRACER_RAYTRACERBASIC_H


#include "Scene.h"
#include "Color.h"

class RayTracer{
protected:
    Scene scene;

public:
    explicit RayTracer(Scene scene);
    Color traceRay(Ray ray);
    Color calcColor(Point point);
};


#endif //RAYTRACER_RAYTRACERBASIC_H