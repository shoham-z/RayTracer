//
// Created by shoham on 6/18/22.
//

#include "Color.h"

Color::Color(double r, double g, double b) {
    if (r < 0 || g < 0 || b < 0) { exit(-1); }
    this->r = r;
    this->g = g;
    this->b = b;
}

Color Color::scale(double k) {
    if (k < 0.0) exit(-1);
    return {this->r*k,this->g*k,this->b*k};
}

Color Color::reduce(double k) {
    if (k < 1.0) exit(-1);
    return {this->r / k,this->g / k,this->b / k};
}

Color Color::add(const std::list<Color> &colors) {
    double rr = this->r;
    double rg = this->g;
    double rb = this->b;
    for (Color c : colors) {
        rr += c.r;
        rg += c.g;
        rb += c.b;
    }
    return {rr, rg, rb};
}

Color Color::add(Color color) {
    return {this->r + color.r, this->g + color.g, this->b + color.b};
}

Color Color::scale(Point k) {
    if (k.getX() < 0.0 || k.getY() < 0.0 || k.getZ() < 0.0) exit(-1);
        return {this->r*k.getX(),this->g*k.getY(),this->b*k.getZ()};
}

Color Color::reduce(Point k) {
    if (k.getX() < 0.0 || k.getY() < 0.0 || k.getZ() < 0.0) exit(-1);
    return {this->r/k.getX(),this->g/k.getY(),this->b/k.getZ()};}

Color Color::operator=(struct Color *other) {
    return *other;
}

int Color::getR() {
    return (int)this->r % 256;
}

int Color::getG() {
    return (int)this->g % 256;
}

int Color::getB() {
    return (int)this->b % 256;
}

Color::Color() {
    this->r = 0;
    this->g= 0;
    this->b = 0;
}



