//
// Created by shoham on 6/16/22.
//

#include "geometries/Geometry.h"

Material Geometry::getMaterial() {
    return this->material;
}
Color Geometry::getEmission(){
    return this->emission;
}
