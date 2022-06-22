//
// Created by shoham on 6/21/22.
//

#include "lights/DirectionalLight.h"

DirectionalLight::DirectionalLight(Vector dir, Color color) : dir(dir.normalize()) {
    this->color = color;
}

Color DirectionalLight::getColor(Point p) {
    return this->color;
}

Vector DirectionalLight::getL(Point p) {
    return this->dir;
}

double DirectionalLight::getDistance(Point p) {
    return std::numeric_limits<double>::max();
}
