//
// Created by shoham on 6/17/22.
//

#include "renderer/RayTracer.h"

#include <utility>

RayTracer::RayTracer(Scene scene) : scene(std::move(scene)) {

}

Color RayTracer::traceRay(Ray ray) {
    GeoPoint closestPoint = findClosestIntersection(ray);
    return (!closestPoint) ? this->scene.background : calcColor(closestPoint, ray, depth, INITIAL_K).add(this->scene.ambientLight.getColor());

}

Color RayTracer::calcColor(GeoPoint geoPoint, Ray ray, int level, double k) {
    if (!geoPoint) return Color::black();
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
            Vector lightDirection = l.scale(-1);
            double ktr = -1;

            // transparency check
            double lightDistance = lightSource->getDistance(geoPoint.point);
            Ray reflectedRay = {geoPoint.point, lightDirection, n};
            std::list<GeoPoint> intersections = this->scene.geometries
                    .findGeoIntersections(reflectedRay, lightDistance);
            if (intersections.empty()) {ktr =  1;}

            if (ktr ==-1) {
                ktr = 1;
                for (GeoPoint intersection: intersections) {
                    if (Util::alignZero(intersection.point.distance(geoPoint.point) - lightDistance) <= 0) {
                        ktr = intersection.geometry->getMaterial().transparent * ktr;
                        if (ktr < MIN_CALC_COLOR_K) {
                            ktr = 0;
                            break;
                        }
                    }
                }
            }
            // transparency check end

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
    color = this->scene.ambientLight.getColor()
            .add(color);

    //
    if( 1 == level) return color;
    double kkr = k * material.reflective;
    if (kkr >= MIN_CALC_COLOR_K)
        color = color.add(
                calcGlobalEffect({geoPoint.point, v.subtract(n.scale(2 * n.dotProduct(v))), n}, level, material.reflective, kkr));
    double kkt = k * material.transparent;
    if (kkt >= MIN_CALC_COLOR_K)
        color = color.add(
                calcGlobalEffect({geoPoint.point, v, n}, level, material.transparent, kkt));
    return color;

}

GeoPoint RayTracer::findClosestIntersection(Ray ray) {
    std::list<GeoPoint> intersections = this->scene.geometries.findGeoIntersections(ray);
    return (intersections.empty()) ? GeoPoint() : ray.findClosestGeoPoint(intersections);
}

Color RayTracer::calcGlobalEffect(Ray ray, int level, double kx, double kkx) {
    GeoPoint gp = findClosestIntersection(ray);
    return (!gp ? this->scene.background : calcColor(gp, ray, level - 1, kkx)).scale(kx);
}

