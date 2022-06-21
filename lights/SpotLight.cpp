//
// Created by shoham on 6/21/22.
//
#include "Util.h"
#include "lights/SpotLight.h"

SpotLight::SpotLight(Point position, Vector dir, Color color) : dir(dir.normalize()), PointLight(position, color) {
}

Color SpotLight::getColor(Point p) {
    double v = this->dir.dotProduct(this->getL(p));
    if (Util::alignZero(v) <= 0) return Color::black();
    return PointLight::getColor(p).scale(this->beam == 1 ? v : pow(v, this->beam));
}

Vector SpotLight::getL(Point p) {
    return p.subtract(this->position).normalize();
}

PointLight SpotLight::setNarrowBeam(int i) {
    // I is to compute (cos(angle))^i to get narrower beam
    this->beam = i;
    return *this;

}
