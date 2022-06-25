//
// Created by shoham on 6/16/22.
//

#include "geometries/Geometry.h"

Color Geometry::getEmission() {
    return this->emission;
}

Material Geometry::getMaterial() {
    return this->material;
}