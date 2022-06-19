//
// Created by shoham on 6/19/22.
//

#ifndef RAYTRACER_CAMERATESTS_H
#define RAYTRACER_CAMERATESTS_H

#include "Ray.h"

void testConstructRay();
void assertEquals(Ray expected, Ray actual, const std::string& message);
#endif //RAYTRACER_CAMERATESTS_H
