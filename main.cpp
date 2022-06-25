#include "primitives/Vector.h"
#include "primitives/Point.h"
#include "primitives/Ray.h"
#include "geometries/Sphere.h"
#include "geometries/Plane.h"
#include "geometries/Triangle.h"
#include "renderer/Camera.h"
#include "geometries/Geometries.h"
#include "lights/DirectionalLight.h"
#include "lights/SpotLight.h"
#include "lights/PointLight.h"
#include "tests/LightsTest.h"
#include "tests/reflectionTranparencyTests.h"

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
    scene.geometries.add(std::make_shared<Sphere>(sphere));
    Triangle triangle1 = Triangle(Point(-100, 0, -100), Point(0, 100, -100), Point(-100, 100, -100)); // up
    scene.geometries.add(std::make_shared<Triangle>(triangle1));
    // left
    Triangle triangle2 = Triangle(Point(-100, 0, -100), Point(0, -100, -100), Point(-100, -100, -100)); // down left
    scene.geometries.add(std::make_shared<Triangle>(triangle2));

    Triangle triangle3 = Triangle(Point(100, 0, -100), Point(0, -100, -100), Point(100, -100, -100)); // down
    scene.geometries.add(std::make_shared<Triangle>(triangle3));

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
    scene.geometries.add(std::make_shared<Sphere>(sphere));
    // up left

    //Pointers are bad idea
    Triangle triangle1 = Triangle(Point(-100, 0, -100), Point(0, 100, -100), Point(-100, 100, -100));
            triangle1.setEmission(Color::green());
    scene.geometries.add(std::make_shared<Triangle>(triangle1));


    // down left
    Triangle triangle2 = Triangle(Point(-100, 0, -100), Point(0, -100, -100), Point(-100, -100, -100));
            triangle2.setEmission(Color::red());
    scene.geometries.add(std::make_shared<Triangle>(triangle2));

    // down right
    Triangle triangle3 = Triangle(Point(100, 0, -100), Point(0, -100, -100), Point(100, -100, -100));
            triangle3.setEmission(Color::blue());
    scene.geometries.add(std::make_shared<Triangle>(triangle3));

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
    //gridTest();
    //basicRenderTest();
    //basicRenderMultiColorTest();
    LightsTests();
    reflectionTranparencyTests::trianglesTransparentSphere();
    reflectionTranparencyTests::twoSpheres();
    reflectionTranparencyTests::twoSpheresOnMirrors();
    return 0;
}