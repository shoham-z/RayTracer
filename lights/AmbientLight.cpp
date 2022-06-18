//
// Created by shoham on 6/18/22.
//

#include "AmbientLight.h"

AmbientLight::AmbientLight(Color iA, Point kA) {
        this->intensity = Color(iA.scale(kA));
}

AmbientLight::AmbientLight() {
    this->intensity = Color::black();

}

Color AmbientLight::getIntensity() {
    return this->intensity;
}


