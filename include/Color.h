//
// Created by shoham on 6/18/22.
//
#include <iostream>
#include <list>
#include "Point.h"

#ifndef RAYTRACER_COLOR_H
#define RAYTRACER_COLOR_H


class Color {
public:
    double r, g, b;

    static Color red() { return {255, 0, 0}; }

    static Color green() { return {0, 255, 0}; }

    static Color blue() { return {0, 0, 255}; }

    static Color black() { return {0, 0, 0}; }

    static Color white() { return {255, 255, 255}; }

    Color(double r, double g, double b);

    Color scale(double k);

    Color scale(Point k);

    Color reduce(double k);

    Color reduce(Point k);

    Color add(const std::list<Color> &colors);

    Color add(Color color);

    Color operator=(struct Color *other);

    int getR();
    int getG();
    int getB();
};


#endif //RAYTRACER_COLOR_H
