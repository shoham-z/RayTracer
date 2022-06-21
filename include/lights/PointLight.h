//
// Created by shoham on 6/21/22.
//

#ifndef RAYTRACER_POINTLIGHT_H
#define RAYTRACER_POINTLIGHT_H

#include "LightSource.h"
#include "Light.h"

class PointLight : public Light, public LightSource {
    double kC, kL, kQ;
protected:
    Point position;
public:
    PointLight(Point position, Color color);

    PointLight setKc(double k);

    PointLight setKq(double k);

    Color getColor(Point p) override;

    Vector getL(Point p) override;

    PointLight setKl(double k);
};


#endif //RAYTRACER_POINTLIGHT_H
