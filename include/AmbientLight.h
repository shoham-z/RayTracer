//
// Created by shoham on 6/18/22.
//

#ifndef RAYTRACER_AMBIENTLIGHT_H
#define RAYTRACER_AMBIENTLIGHT_H


#include "Color.h"
#include "Point.h"

class AmbientLight {
    Color intensity = Color(0, 0, 0);

public:
    AmbientLight(Color iA, Point kA);
    AmbientLight();
    Color getIntensity();
};


#endif //RAYTRACER_AMBIENTLIGHT_H
