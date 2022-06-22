//
// Created by shoham on 6/21/22.
//

#ifndef RAYTRACER_LIGHTSOURCE_H
#define RAYTRACER_LIGHTSOURCE_H

#include "primitives/Color.h"
#include "primitives/Vector.h"
#include "primitives/Point.h"

class LightSource {

public:
    virtual Color getColor(Point p) = 0;

    virtual Vector getL(Point p) = 0;

    virtual double getDistance(Point p) = 0;
};


#endif //RAYTRACER_LIGHTSOURCE_H
