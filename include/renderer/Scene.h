//
// Created by shoham on 6/17/22.
//

#ifndef RAYTRACER_SCENE_H
#define RAYTRACER_SCENE_H


#include <memory>
#include "geometries/Geometries.h"
#include "lights/AmbientLight.h"
#include "lights/LightSource.h"

class Scene {
public:
    std::string name;
    Geometries geometries = Geometries();
    Color background = Color::black();
    AmbientLight ambientLight = AmbientLight(Color(), Point());
    std::list< std::shared_ptr<LightSource>> lights;

    Scene(std::string name);

    Scene setGeometries(Geometries geometries);

    Scene addGeometry(const std::shared_ptr<Geometry>& geometry);

    Scene setLights(const std::shared_ptr<LightSource>& lights);

    Scene addLight(const std::shared_ptr<LightSource>& lightSource);

    Scene setAmbientLight(AmbientLight light);

    Scene setBackground(Color background);

};

#endif //RAYTRACER_SCENE_H
