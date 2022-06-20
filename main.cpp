#include "include/Vector.h"
#include "include/Point.h"
#include "include/Ray.h"
#include "include/Sphere.h"
#include "include/Plane.h"
#include "include/Triangle.h"
#include "include/Util.h"
#include "include/Camera.h"
#include "include/Geometries.h"
#include "CameraTests.h"
#include "sphereTests.h"

void gridTest() {
    Scene scene = Scene("Test scene")
            .setAmbientLight(AmbientLight(Color::red(), Point(1, 1, 1))) //
            .setBackground(Color::red());

    Camera camera = Camera(Point::ZERO(), Vector(0, 0, -1), Vector(0, 1, 0)) //
            .setVPDistance(100) //
            .setVPSize(500, 500) //
            .setImageWriter(ImageWriter("grid test", 1000, 1000))
            .setRayTracer(RayTracer(scene));

    camera.renderImage();
    camera.printGrid(100, Color(255, 255, 0));
    camera.writeToImage();
}

void basicRenderTest() {
    Scene scene = Scene("Test scene")//
            .setAmbientLight(AmbientLight(Color(255, 191, 191), //
                                          Point(1, 1, 1))) //
            .setBackground(Color(75, 127, 90));

    Sphere sphere = Sphere(Point(0, 0, -100), 50);
    scene.geometries.add(&sphere);
    Triangle triangle1 = Triangle(Point(-100, 0, -100), Point(0, 100, -100), Point(-100, 100, -100)); // up
    scene.geometries.add(&triangle1);
    // left
    Triangle triangle2 = Triangle(Point(-100, 0, -100), Point(0, -100, -100), Point(-100, -100, -100)); // down left
    scene.geometries.add(&triangle2);

    Triangle triangle3 = Triangle(Point(100, 0, -100), Point(0, -100, -100), Point(100, -100, -100)); // down
    scene.geometries.add(&triangle3);

    // right
    Camera camera = Camera(Point::ZERO(), Vector(0, 0, -1), Vector(0, 1, 0)) //

            .setVPDistance(100) //
            .setVPSize(500, 500) //
            .setImageWriter(ImageWriter("base render test", 1000, 1000))
            .setRayTracer(RayTracer(scene));

    camera.renderImage();
    camera.printGrid(100, Color::blue().add(Color::red()));
    camera.writeToImage();
}

void basicRenderMultiColorTest() {
    Scene scene = Scene("Test scene")//
            .setAmbientLight(AmbientLight(Color::white(), Point(0.2, 0.2, 0.2))); //



    Sphere sphere = Sphere(Point(0, 0, -100), 50);
    scene.geometries.add(&sphere);
    // up left

    //Pointers are bad idea
    Triangle triangle1 = Triangle(Point(-100, 0, -100), Point(0, 100, -100), Point(-100, 100, -100));
            triangle1.setEmission(Color::green());
    scene.geometries.add(&triangle1);


    // down left
    Triangle triangle2 = Triangle(Point(-100, 0, -100), Point(0, -100, -100), Point(-100, -100, -100));
            triangle2.setEmission(Color::red());
    scene.geometries.add(&triangle2);

    // down right
    Triangle triangle3 = Triangle(Point(100, 0, -100), Point(0, -100, -100), Point(100, -100, -100));
            triangle3.setEmission(Color::blue());
    scene.geometries.add(&triangle3);

    Camera camera = Camera(Point::ZERO(), Vector(0, 0, -1), Vector(0, 1, 0)) //
            .setVPDistance(100) //
            .setVPSize(500, 500) //
            .setImageWriter(ImageWriter("color render test", 1000, 1000))
            .setRayTracer(RayTracer(scene));

    camera.renderImage();
    camera.printGrid(100, Color::white());
    camera.writeToImage();
}

int main() {
    testGetNormal();
    testConstructRay();
    testFindIntersections();
    //gridTest();
    //basicRenderTest();
    basicRenderMultiColorTest();
    return 0;
}