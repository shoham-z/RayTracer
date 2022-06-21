//
// Created by shoham on 6/21/22.
//

#include "lights/Light.h"


Color Light::getColor() {
    return this->color;
}

Light::Light(Color color) {
    this->color = color;

}

Light::Light() {

}
