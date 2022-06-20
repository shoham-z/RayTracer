//
// Created by shoham on 6/17/22.
//

#include "RayTracer.h"

RayTracer::RayTracer(Scene scene) : scene(scene) {

}

Color RayTracer::traceRay(Ray ray) {
    std::list<GeoPoint> intersections = scene.geometries.findGeoIntersections(ray);
    if (intersections.empty()) return scene.background;
    GeoPoint closestPoint = ray.findClosestGeoPoint(intersections);
    Color color =calcColor(closestPoint);
    return color;
}

Color RayTracer::calcColor(GeoPoint geoPoint) {
    Color emission = geoPoint.geometry->getEmission();
    return scene.ambientLight.getIntensity()
            .add(emission);
}

