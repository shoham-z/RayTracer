//
// Created by shoham on 6/21/22.
//

#ifndef RAYTRACER_DIRECTIONALLIGHT_H
#define RAYTRACER_DIRECTIONALLIGHT_H

#include "LightSource.h"
#include "Light.h"

class DirectionalLight : public Light, public LightSource {
    Vector dir;
public:
    DirectionalLight(Vector dir, Color color);

    Color getColor(Point p) override;

    Vector getL(Point p) override;

    double getDistance(Point p) override;
};


#endif //RAYTRACER_DIRECTIONALLIGHT_H
