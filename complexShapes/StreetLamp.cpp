//
// Created by shoham on 7/17/22.
//

#include "copmlexShapes/StreetLamp.h"
#include "geometries/Cylinder.h"

StreetLamp::StreetLamp(Point point, double height, Color color, Vector up, double radius) : light(
        PointLight(point.add(up.normalize().scale(height + radius * 3)), color)
                .setKl(0.00001).setKq(0.00001)) {
Sphere temp = Sphere(point.add(up.normalize().scale(height + radius *3)),radius * 3)
        .setEmission(color)
        .setMaterial(Material().setTransparent(1));
    this->geometries.addShared(std::make_shared<Sphere>(temp));
    this->geometries.addShared(std::make_shared<Cylinder>(Cylinder(Ray(point, up), radius, height)
    .setEmission(Color(127, 127, 127).scale(1.25))
    .setMaterial(Material().setTransparent(0.3))));

}
