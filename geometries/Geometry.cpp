//
// Created by shoham on 6/16/22.
//

#include "geometries/Geometry.h"

Color Geometry::getEmission() {
    return this->emission;
}
Geometry* Geometry::setEmission(Color emission) {
    this->emission = emission;
    return this;
}
Material Geometry::getMaterial(){
    return this->material;
}
Geometry* Geometry::setMaterial(Material material) {
    this->material = material;
    return this;
}
