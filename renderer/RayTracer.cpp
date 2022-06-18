//
// Created by shoham on 6/17/22.
//

#include "RayTracer.h"

RayTracer::RayTracer(Scene scene) : scene(scene) {

}

Color RayTracer::traceRay(Ray ray) {
    std::list<Point> intersections = this->scene.geometries.findIntersections(ray);
    if(intersections.empty()) return this->scene.background;
    Point closest = ray.findClosestPoint(intersections);
    return calcColor(closest);
}

Color RayTracer::calcColor(Point point) {
    return this->scene.ambientLight.getIntensity();
}

