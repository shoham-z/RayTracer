//
// Created by shoham on 6/21/22.
//

#ifndef RAYTRACER_POINTLIGHT_H
#define RAYTRACER_POINTLIGHT_H

#include "LightSource.h"
#include "Light.h"

class PointLight : public Light, public LightSource {
protected:
    Point position;
    double kQ;
    double kL;
    double kC;
public:
    PointLight(Point position, Color color);

    PointLight setKc(double k);

    PointLight setKl(double k);

    PointLight setKq(double k);

    Color getColor(Point p) override;

    Vector getL(Point p) override;

    double getDistance(Point p) override;

};


#endif //RAYTRACER_POINTLIGHT_H
