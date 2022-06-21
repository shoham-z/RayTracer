//
// Created by shoham on 6/18/22.
//

#include "lights/AmbientLight.h"

AmbientLight::AmbientLight(Color iA, Point kA) : Light(iA.scale(kA)) {
}

AmbientLight::AmbientLight() : Light() {

}



