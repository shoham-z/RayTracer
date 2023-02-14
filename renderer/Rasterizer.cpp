//
// Created by shoham on 2/14/23.
//

#include "renderer/Rasterizer.h"

Rasterizer::Rasterizer(Scene scene) : scene(std::move(scene)) {

}

Scene Rasterizer::getScene() {
    return this->scene;
}
