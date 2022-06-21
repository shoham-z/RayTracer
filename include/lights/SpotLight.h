//
// Created by shoham on 6/21/22.
//

#ifndef RAYTRACER_SPOTLIGHT_H
#define RAYTRACER_SPOTLIGHT_H

#include "PointLight.h"

class SpotLight : public PointLight {
    int beam;
    Vector dir;

public:
    SpotLight(Point position, Vector dir, Color color);

    Color getColor(Point p) override;

    Vector getL(Point p) override;

    PointLight setNarrowBeam(int i);
};


#endif //RAYTRACER_SPOTLIGHT_H
