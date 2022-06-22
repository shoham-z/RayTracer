//
// Created by shoham on 6/17/22.
//

#include "renderer/RayTracer.h"

RayTracer::RayTracer(Scene scene) : scene(scene) {

}

Color RayTracer::traceRay(Ray ray) {
    std::list<GeoPoint> intersections = this->scene.geometries.findGeoIntersections(ray);
    if (intersections.empty()) return this->scene.background;
    GeoPoint closestPoint = ray.findClosestGeoPoint(intersections);
    Color color = calcColor(closestPoint, ray);
    return color;
}

Color RayTracer::calcColor(GeoPoint geoPoint, Ray ray) {
    Color color = geoPoint.geometry->getEmission();
    Vector v = ray.getDirection();
    Vector n = geoPoint.geometry->getNormal(geoPoint.point);
    double nv = Util::alignZero(n.dotProduct(v));
    if (nv == 0) return color;
    Material material = geoPoint.geometry->getMaterial();
    for (auto& lightSource: this->scene.lights) {
        Vector l = lightSource->getL(geoPoint.point);
        double nl = Util::alignZero(n.dotProduct(l));
        if (nl * nv > 0) { // sign(nl) == sing(nv)
            Color iL = lightSource->getColor(geoPoint.point);

            // diffusive
            color = color.add(iL.scale(material.diffusive * std::abs(nl)));

            // specular
            Vector minusR = n.scale(2 * nl).subtract(l);
            double minusVR = minusR.dotProduct(v);
            color = color.add(iL.scale((minusVR <= 0)? 0 :material.specular * (std::pow(minusVR, material.shininess))));
            // speculat
        }
    }
    return this->scene.ambientLight.getColor()
            .add(color);
}
