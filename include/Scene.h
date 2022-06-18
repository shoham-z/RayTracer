//
// Created by shoham on 6/17/22.
//

#ifndef RAYTRACER_SCENE_H
#define RAYTRACER_SCENE_H


#include "Geometries.h"
#include "AmbientLight.h"

class Scene {
public:
    std::string name;
    Geometries geometries = Geometries();
    Color background = Color::black();
    AmbientLight ambientLight = AmbientLight();

    Scene(std::string name);

    Scene setGeometries(Geometries geometries);

    Scene setAmbientLight(AmbientLight light);

    Scene setBackground(Color background);

};
#endif //RAYTRACER_SCENE_H
