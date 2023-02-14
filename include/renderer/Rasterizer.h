//
// Created by shoham on 2/14/23.
//

#ifndef RAYTRACER_RASTERIZER_H
#define RAYTRACER_RASTERIZER_H


#include "Scene.h"

class Rasterizer {
public:
    explicit Rasterizer(Scene scene);

    Scene getScene();

protected:
    Scene scene;


};


#endif //RAYTRACER_RASTERIZER_H
