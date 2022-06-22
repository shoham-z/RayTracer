//
// Created by shoham on 6/17/22.
//
#ifndef RAYTRACER_RAYTRACERBASIC_H
#define RAYTRACER_RAYTRACERBASIC_H


#include "Scene.h"
#include "primitives/Color.h"

class RayTracer{
protected:
    Scene scene;
    double DELTA = 0.1;

public:
    explicit RayTracer(Scene scene);
    Color traceRay(Ray ray);
    Color calcColor(GeoPoint geoPoint, Ray ray);
private:
    bool unshaded(GeoPoint gp, std::shared_ptr<LightSource> lightSource, Vector n, double nv);

};


#endif //RAYTRACER_RAYTRACERBASIC_H
