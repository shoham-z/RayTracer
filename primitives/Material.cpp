//
// Created by shoham on 6/18/22.
//

#include "primitives/Material.h"

Material Material::setSpecular(double s) {
    this->specular = s;
    return *this;
}

Material Material::setDiffusive(double d) {
    this->diffusive = d;
    return *this;
}

Material Material::setShininess(int shine) {
    this->shininess = shine;
    return * this;
}

Material::Material() {

}
