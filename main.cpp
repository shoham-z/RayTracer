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
#include "tests/reflectionTransparencyTests.h"
#include "geometries/Tube.h"

void gridTest();

void basicRenderTest();

void basicRenderMultiColorTest();

void tubeTest() {
    Camera camera = Camera(Point(0, 0, -1000), Vector(0, 0, 1), Vector(0, 1, 0))
            .setVPSize(160, 160) // 16x9 scaled by 20
            .setVPDistance(1000);

    Scene scene = Scene("Tube");//.setBackground(Color(135, 206, 235));
    //.setAmbientLight(AmbientLight(Color(249,215,28),Double3(0.5)))

    scene.addGeometry(
            std::make_shared<Tube>(Tube(Ray(Point(0, 0, 50), camera.getvTo().subtract(camera.getvUp())), 50)
                                               .setMaterial(Material().setDiffusive(0.5).setSpecular(0.5).setShininess(
                                                       20).setTransparent(0))
                                               .setEmission(Color::red().reduce(2))));


    scene.addLight(std::make_shared<SpotLight>(SpotLight(Point(100, 100, 0), Vector(-1, -1, 1), Color(255, 0, 255))
                             .setNarrowBeam(10).setKl(0.00001).setKq(0.00001)));
    scene.addLight(std::make_shared<SpotLight>(SpotLight(Point(-100, -100, 0), Vector(1, 1, 1),Color::red().add(Color::blue()))
                             .setNarrowBeam(10).setKl(0.00001).setKq(0.00001)));

    ImageWriter imageWriter = ImageWriter("Tube", 500, 500);
    camera.setImageWriter(imageWriter) //
            .setRayTracer(RayTracer(scene)) //
            .renderImage() //
            .writeToImage(); //
}

int main() {
    tubeTest();

    gridTest();
    basicRenderTest();
    basicRenderMultiColorTest();
    LightsTests();
    reflectionTransparencyTests::trianglesTransparentSphere();
    reflectionTransparencyTests::twoSpheres();
    reflectionTransparencyTests::twoSpheresOnMirrors();
    return 0;
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