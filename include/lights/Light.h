//
// Created by shoham on 6/21/22.
//

#ifndef RAYTRACER_LIGHT_H
#define RAYTRACER_LIGHT_H


#include "primitives/Color.h"

class Light {
protected:
    Color color = Color(0, 0, 0);
public:
    explicit Light(Color color);
    Light();
    Color getColor();

};


#endif //RAYTRACER_LIGHT_H
