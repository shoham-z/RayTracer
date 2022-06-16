#include <iostream>
#include "include/Vector.h"
#include "include/Point.h"
#include "include/Ray.h"
#include "include/Sphere.h"

int main() {
    Sphere sphere = Sphere(23, Point(0, 1, 0));
    Point point = Point(0,24,0);
    Vector normal = sphere.getNormal(point);
    std::cout << normal << std::endl;

    return 0;
}

