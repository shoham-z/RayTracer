//
// Created by shoham on 6/17/22.
//
#ifndef RAYTRACER_RAYTRACERBASIC_H
#define RAYTRACER_RAYTRACERBASIC_H


#include "Scene.h"
#include "primitives/Color.h"

class RayTracer {
    static const int INITIAL_K = 1;
    int depth = 10;
    constexpr static const double MIN_CALC_COLOR_K = 0.001;
protected:
    Scene scene;
    double DELTA = 0.1;

public:
    explicit RayTracer(Scene scene);

    Color traceRay(Ray ray);

private:
    Color calcColor(GeoPoint geoPoint, Ray ray);
    Color calcGlobalEffect(Ray ray, int level, double kx, double kkx);

    Color calcColor(GeoPoint gp, Ray ray, int level, double k);

    GeoPoint findClosestIntersection(Ray ray);
};


#endif //RAYTRACER_RAYTRACERBASIC_H
