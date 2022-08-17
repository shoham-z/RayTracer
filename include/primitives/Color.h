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
    double_t r, g, b;

    static Color red() { return {1, 0, 0}; }

    static Color green() { return {0, 1, 0}; }

    static Color blue() { return {0, 0, 1}; }

    static Color black() { return {0, 0, 0}; }

    static Color white() { return {1, 1, 1}; }

    Color(double r, double g, double b);
    Color();

    Color scale(double k) const;

    Color reduce(double k) const;

    Color add(const std::list<Color> &colors) const;

    Color add(Color color);

    Color operator=(Color *other);

    bool operator==(Color other) const;

    friend std::ostream &operator<<(std::ostream &os, Color &color);

    double_t getR();
    double_t getG();
    double_t getB();

    static bool equal(Color* colors, uint size);
    static Color average(Color* colors, uint size);
};


#endif //RAYTRACER_COLOR_H
