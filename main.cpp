#include <iostream>
#include "include/Vector.h"
#include "include/Point.h"
#include "include/Ray.h"
#include "include/Sphere.h"
#include "include/Util.h"
#include "include/Camera.h"
#include "include/Geometries.h"

int main() {
    Sphere sphere1 = Sphere(23, Point(0, 1, 0));
    Sphere sphere2 = Sphere(2, Point(0, 1, 0));
    std::list<Geometry*> spheres;
    spheres.push_back(&sphere1);
    spheres.push_back(&sphere2);
    Geometries geometries = Geometries();
    geometries.add(spheres);
    Point point = Point(0,24,0);
    Vector normal = sphere1.getNormal(point);
    std::cout << normal << std::endl;
    Ray ray = Ray(Point(100,1,0), Vector(-1,0,0));
    std::list<Point> intersections = geometries.findIntersections(ray);
    for (Point point: intersections) {
        std::cout << point<< std::endl;
    }
    Camera camera = Camera(Point(0,0,-1000), Vector(0,0,1),Vector(0,1,0))
            .setVPSize(300,300).setVPDistance(1000);
    camera.renderImage();

    return 0;
}

