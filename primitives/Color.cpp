//
// Created by shoham on 6/18/22.
//

#include "primitives/Color.h"

Color::Color(double r, double g, double b) {
    this->r = r;
    this->g = g;
    this->b = b;
    if (r < 0) {
        this->r *= -1;
    }
    if (g < 0) {
        this->g *= -1;
    }
    if (b < 0) {
        this->b *= -1;
    }
}

Color Color::scale(double k) const {
    if (k < 0.0) exit(-1);
    return {this->r * k, this->g * k, this->b * k};
}

Color Color::reduce(double k) const {
    if (k < 1.0) exit(-1);
    return {this->r / k, this->g / k, this->b / k};
}

Color Color::add(const std::list<Color> &colors) const {
    double rr = this->r;
    double rg = this->g;
    double rb = this->b;
    for (Color c: colors) {
        rr += c.r;
        rg += c.g;
        rb += c.b;
    }
    return {rr, rg, rb};
}

Color Color::add(Color color) {
    return {this->r + color.r, this->g + color.g, this->b + color.b};
}

Color Color::operator=(struct Color *other) {
    return *other;
}

double_t Color::getR() {
    return this->r > 1.0 ? 1.0 : this->r;
}

double_t Color::getG() {
    return this->g > 1.0 ? 1.0 : this->g;
}

double_t Color::getB() {
    return this->b > 1.0 ? 1.0 : this->b;
}

Color::Color() {
    this->r = 0;
    this->g = 0;
    this->b = 0;
}

std::ostream &operator<<(std::ostream &os, Color &color) {
    os << "point(" << color.r << ", " << color.g << ", " << color.b << ")";
    return os;
}

bool Color::operator==(Color other) const {
    return (this->r == other.r && this->b == other.b && this->g == other.g);
}

bool Color::equal(Color *colors, uint size) {
    for (int i = 0; i < size - 1; ++i) {
        if(!(colors[i] == colors[i+1])){
            return false;
        }
    }
    return true;
}

Color Color::average(Color *colors, uint size) {
    std::list<Color> cs;

    for (int i = 0; i < size; i++) {
        cs.push_back(colors[i]);
    }
    Color average = colors[0].add(cs);
    return average.reduce(size);
}



