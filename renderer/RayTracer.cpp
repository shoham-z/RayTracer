//
// Created by shoham on 6/17/22.
//

#include "renderer/RayTracer.h"

#include <utility>

RayTracer::RayTracer(Scene scene) : scene(std::move(scene)) {

}

Color RayTracer::traceRay(Ray ray) {
    GeoPoint closestPoint = findClosestIntersection(ray);
    return (!closestPoint) ? this->scene.background : calcColor(closestPoint, ray);

}

Color RayTracer::calcColor(GeoPoint geoPoint, Ray ray) {
    return calcColor(geoPoint, ray, MAX_CALC_COLOR_LEVEL, MIN_CALC_COLOR_K).add(this->scene.ambientLight.getColor());
}

double RayTracer::transparency(GeoPoint gp, const std::shared_ptr<LightSource> &light, Vector l, Vector n) {
    Vector lightDirection = l.scale(-1);
    double lightDistance = light->getDistance(gp.point);
    Ray ray = constructRefractedRay(gp.point, lightDirection, n);
    std::list<GeoPoint> intersections = this->scene.geometries
            .findGeoIntersections(ray, lightDistance);
    if (intersections.empty()) return 1;
    double ktr = 1;

    for (GeoPoint intersection: intersections) {
        if (Util::alignZero(intersection.point.distance(gp.point) - lightDistance) <= 0) {
            ktr = intersection.geometry->getMaterial().transparent * ktr;
            if (ktr < MIN_CALC_COLOR_K) return 0;
        }
    }

    return ktr;
}

Color RayTracer::calcColor(GeoPoint gp, Ray ray, int level, double k) {
    Color color = calcLocalEffects(gp, ray, k);
    return 1 == level ? color : color.add(calcGlobalEffects(gp, ray.getDirection(), level, k));
}

Color RayTracer::calcLocalEffects(GeoPoint geoPoint, Ray ray, double k) {
    Color color = geoPoint.geometry->getEmission();
    Vector v = ray.getDirection();
    Vector n = geoPoint.geometry->getNormal(geoPoint.point);
    double nv = Util::alignZero(n.dotProduct(v));
    if (nv == 0) return color;
    Material material = geoPoint.geometry->getMaterial();
    for (auto &lightSource: this->scene.lights) {
        Vector l = lightSource->getL(geoPoint.point);
        double nl = Util::alignZero(n.dotProduct(l));
        if (nl * nv > 0) { // sign(nl) == sing(nv)
            double ktr = transparency(geoPoint, lightSource, l, n);
            if (k * ktr >= MIN_CALC_COLOR_K) {
                Color iL = lightSource->getColor(geoPoint.point).scale(ktr);

                // diffusive
                color = color.add(iL.scale(material.diffusive * std::abs(nl)));

                // specular
                Vector minusR = n.scale(2 * nl).subtract(l);
                double minusVR = minusR.dotProduct(v);
                color = color.add(
                        iL.scale((minusVR <= 0) ? 0 : material.specular * (std::pow(minusVR, material.shininess))));
                // specular
            }
        }
    }
    return this->scene.ambientLight.getColor()
            .add(color);
}

bool RayTracer::unshaded(GeoPoint gp, const std::shared_ptr<LightSource>& lightSource, Vector n, double nv) {
    Vector lightDirection = lightSource->getL(gp.point).scale(-1); // from point to light source
    Vector epsVector = n.scale(nv < 0 ? this->DELTA : -this->DELTA);
    Point point = gp.point.add(epsVector);
    Ray lightRay = Ray(point, lightDirection);
    double lightDistance = lightSource->getDistance(gp.point);
    std::list<GeoPoint> intersections = scene.geometries.findGeoIntersections(lightRay, lightDistance);
    return intersections.empty();
}

Ray RayTracer::constructRefractedRay(Point point, Vector v, Vector n) {
    return {point, v, n};
}

Ray RayTracer::constructReflectedRay(Point point, Vector v, Vector n) {
    double nv = n.dotProduct(v);
    return {point, v.subtract(n.scale(2 * nv)), n};
}

GeoPoint RayTracer::findClosestIntersection(Ray ray) {
    std::list<GeoPoint> intersections = this->scene.geometries.findGeoIntersections(ray);
    return (intersections.empty()) ? GeoPoint() : ray.findClosestGeoPoint(intersections);

}

Color RayTracer::calcGlobalEffect(Ray ray, int level, double kx, double kkx) {
    GeoPoint gp = findClosestIntersection(ray);
    return (!gp ? scene.background : calcColor(gp, ray, level - 1, kkx)).scale(kx);
}

Color RayTracer::calcGlobalEffects(GeoPoint gp, Vector v, int level, double k) {
    Color color = Color::black();
    Vector n = gp.geometry->getNormal(gp.point);
    Material material = gp.geometry->getMaterial();
    double kkr = k * material.reflective;
    if (kkr >= MIN_CALC_COLOR_K)
        color = calcGlobalEffect(constructReflectedRay(gp.point, v, n), level, material.reflective, kkr);
    double kkt = k * material.transparent;
    if (kkt >= MIN_CALC_COLOR_K)
        color = color.add(calcGlobalEffect(constructRefractedRay(gp.point, v, n), level, material.transparent, kkt));
    return color;
}
