//
// Created by shoham on 6/21/22.
//

#ifndef RAYTRACER_SPOTLIGHT_H
#define RAYTRACER_SPOTLIGHT_H

#include "PointLight.h"

class SpotLight : public PointLight {
    int beam = 1;
    Vector dir;

public:
    SpotLight(Point position, Vector dir, Color color);

    SpotLight setKc(double k);

    SpotLight setKl(double k);

    SpotLight setKq(double k);

    Color getColor(Point p) override;

    Vector getL(Point p) override;

    SpotLight setNarrowBeam(int i);
};


#endif //RAYTRACER_SPOTLIGHT_H
