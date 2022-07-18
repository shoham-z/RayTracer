//
// Created by shoham on 7/17/22.
//

#ifndef RAYTRACER_HOUSE_H
#define RAYTRACER_HOUSE_H


#include "geometries/Geometries.h"
#include "primitives/Point.h"
#include "primitives/Vector.h"
#include "copmlexShapes/Cube.h"
#include "copmlexShapes/Pyramid.h"

class House {
public:
    Geometries house;


    House(Point baseBottom, double height, Vector up, Vector right);

};


#endif //RAYTRACER_HOUSE_H
