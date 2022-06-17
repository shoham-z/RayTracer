#include <iostream>
#include "include/Vector.h"
#include "include/Point.h"
#include "include/Ray.h"
#include "include/Sphere.h"
#include "include/Util.h"

int main() {
    Sphere sphere = Sphere(23, Point(0, 1, 0));
    Point point = Point(0,24,0);
    Vector normal = sphere.getNormal(point);
    std::cout << normal << std::endl;
    Ray ray = Ray(Point(100,1,0), Vector(-1,0,0));
    std::list<Point> intersections = sphere.findIntersections(ray);
    for (Point point: intersections) {
        std::cout << point<< std::endl;
    }

    return 0;
}

