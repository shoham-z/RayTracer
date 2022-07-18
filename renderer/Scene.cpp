//
// Created by shoham on 6/17/22.
//

#include "renderer/Scene.h"

#include <utility>
#include <memory>

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

Scene Scene::addGeometry(const std::shared_ptr<Geometry>& geometry) {
    this->geometries.addShared(geometry);
    return *this;
}

Scene Scene::setLights(const std::shared_ptr<LightSource>& lights) {

    this->lights.push_back(lights);
    return *this;
}

Scene Scene::addLight(const std::shared_ptr<LightSource>& lightSource) {
    this->lights.push_back(lightSource);
    return *this;
}
