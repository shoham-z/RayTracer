//
// Created by shoham on 7/18/22.
//

#ifndef RAYTRACER_CYLINDER_H
#define RAYTRACER_CYLINDER_H


#include "geometries/Tube.h"
#include "primitives/Ray.h"
#include "geometries/Plane.h"

class Cylinder : public Tube{
    double height;

public:
/**
 * Constructor for Cylinder using an axis ray, radius and height
 *
 * @param ray    the axis ray
 * @param radius the radius
 * @param height the height
 */
    Cylinder(Ray ray, double radius, double height) : Tube(ray, radius) {
        this->height = height;
    }

/**
 * Getter for the height of the Cylinder
 *
 * @return the height
 */
    double getHeight() {
        return this->height;
    }


    Vector getNormal(Point point) override;

    std::list<GeoPoint> findGeoIntersectionsHelper(Ray ray, double maxDistance) override;
Cylinder setMaterial(Material material);
Cylinder setEmission(Color color);
};


#endif //RAYTRACER_CYLINDER_H
