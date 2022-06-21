//
// Created by shoham on 6/18/22.
//

#ifndef RAYTRACER_AMBIENTLIGHT_H
#define RAYTRACER_AMBIENTLIGHT_H

#include "lights/Light.h"
#include "primitives/Color.h"
#include "primitives/Point.h"

class AmbientLight : public Light{

public:
    AmbientLight(Color iA, Point kA);
    AmbientLight();
};


#endif //RAYTRACER_AMBIENTLIGHT_H
