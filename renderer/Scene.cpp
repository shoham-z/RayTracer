//
// Created by shoham on 6/17/22.
//

#include "Scene.h"

#include <utility>

Scene::Scene(std::string name) {
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
