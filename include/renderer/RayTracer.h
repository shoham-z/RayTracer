//
// Created by shoham on 6/17/22.
//
#ifndef RAYTRACER_RAYTRACERBASIC_H
#define RAYTRACER_RAYTRACERBASIC_H


#include "Scene.h"
#include "primitives/Color.h"

class RayTracer {
    static const int INITIAL_K = 1;
    static const int MAX_CALC_COLOR_LEVEL = 10;
    constexpr static const double MIN_CALC_COLOR_K = 0.001;
protected:
    Scene scene;
    double DELTA = 0.1;

public:
    explicit RayTracer(Scene scene);

    Color traceRay(Ray ray);

    Color calcColor(GeoPoint geoPoint, Ray ray);

private:
    Color calcGlobalEffect(Ray ray, int level, double kx, double kkx);

    Color calcGlobalEffects(GeoPoint geoPoint, Vector v, int level, double k);

    double transparency(GeoPoint gp, const std::shared_ptr<LightSource> &light, Vector l, Vector n);

    Color calcLocalEffects(GeoPoint geoPoint, Ray ray, double k);

    Color calcColor(GeoPoint gp, Ray ray, int level, double k);

    static Ray constructRefractedRay(Point point, Vector v, Vector n);

    static Ray constructReflectedRay(Point point, Vector v, Vector n);

    bool unshaded(GeoPoint gp, const std::shared_ptr<LightSource> &lightSource, Vector n, double nv);

    GeoPoint findClosestIntersection(Ray ray);
};


#endif //RAYTRACER_RAYTRACERBASIC_H
