//
// Created by shoham on 6/21/22.
//

#include "lights/PointLight.h"

PointLight::PointLight(Point position, Color color) {
    this->position = position;
    this->color = color;
    this->kC = 1;
    this->kL = 0;
    this->kQ = 0;
}

Color PointLight::getColor(Point p) {
    double distanceSquared = this->position.distanceSquared(p);
    return this->color.scale(1 / (this->kC + this->kL * sqrt(distanceSquared) + this->kQ * distanceSquared));
}

Vector PointLight::getL(Point p) {
    return p.subtract(this->position).normalize();
}

PointLight PointLight::setKc(double k) {
    this->kC = k;
    return *this;
}

PointLight PointLight::setKl(double k) {
    this->kL = k;
    return *this;
}

PointLight PointLight::setKq(double k) {
    this->kQ = k;
    return *this;
}

double PointLight::getDistance(Point p) {
    return this->position.distance(p);
}
