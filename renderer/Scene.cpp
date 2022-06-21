//
// Created by shoham on 6/17/22.
//

#include "renderer/Scene.h"

#include <utility>

Scene::Scene(std::string name) : ambientLight(Color(), Point()) {
    this->name = std::move(name);
}

Scene Scene::setGeometries(Geometries geometries) {
    this->geometries = geometries;
    return *this;
}

Scene Scene::setBackground(Color background) {
    this->background = background;
    return *this;
}

Scene Scene::setAmbientLight(AmbientLight light) {
    this->ambientLight = light;
    return *this;
}

Scene Scene::addGeometry(Geometry& geometry) {
    this->geometries.add(&geometry);
    return *this;
}

Scene Scene::setLights(std::list<LightSource *> lights) {

    this->lights = std::move(lights);
    return *this;
}

Scene Scene::addLight(LightSource& lightSource) {
    this->lights.push_back(&lightSource);
    return *this;
}
