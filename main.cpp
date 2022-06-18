#include <iostream>
#include "include/Vector.h"
#include "include/Point.h"
#include "include/Ray.h"
#include "include/Sphere.h"
#include "include/Util.h"
#include "include/Camera.h"
#include "include/Geometries.h"


int main() {
    Scene scene = Scene("Test scene")
            .setAmbientLight(AmbientLight(Color::red(), Point(1,1,1))) //
            .setBackground( Color::red());

    Camera camera =  Camera(Point::ZERO(),  Vector(0, 0, -1),  Vector(0, 1, 0)) //
    .setVPDistance(100) //
            .setVPSize(500, 500) //
            .setImageWriter( ImageWriter("base render test", 1000, 1000))
            .setRayTracer( RayTracer(scene));

    camera.renderImage();
    camera.printGrid(100, Color(255,255,0));
    camera.writeToImage();
    return 0;
 }