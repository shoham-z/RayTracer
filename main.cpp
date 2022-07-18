#include "primitives/Vector.h"
#include "primitives/Point.h"
#include "primitives/Ray.h"
#include "geometries/Sphere.h"
#include "geometries/Plane.h"
#include "geometries/Triangle.h"
#include "geometries/Polygon.h"
#include "renderer/Camera.h"
#include "geometries/Geometries.h"
#include "lights/DirectionalLight.h"
#include "lights/SpotLight.h"
#include "lights/PointLight.h"
#include "tests/LightsTest.h"
#include "tests/reflectionTransparencyTests.h"
#include "geometries/Tube.h"
#include "copmlexShapes/House.h"
#include "copmlexShapes/StreetLamp.h"

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

void street() {
    Camera camera = Camera(Point(2000, 100, 450), Vector(-2, -0.1, -0.5), Vector(-0.1, 2, 0))
    .setVPSize(200, 200)
            .setVPDistance(1000);

    int howManyHouses = 400;
    double houseSize = 30;

    Scene scene = Scene("GroveStreet").setBackground(Color(2, 25, 60));

    // ****geometries start

    // *group House
    Vector up = Vector(0, 1, 0);
    Vector to = Vector(-1, 0, 0);
    Vector right = Vector(0,0,-1);

    Point housesCenter = Point(-30, -50, -140);

    double step = 2;
    for (int i = 1; i < howManyHouses * step; i += (int)step) {
        scene.geometries.add(House(housesCenter.add(to.scale(houseSize * i)), houseSize, up, to.scale(-1)).house);
    }
    scene.geometries.addShared(std::make_shared<Polygon>(
            Polygon(housesCenter.add(right.scale(-100)), housesCenter.add(right.scale(-300)),
                    housesCenter.add(right.scale(-300)).add(to.scale(600)),
                    housesCenter.add(right.scale(-100)).add(to.scale(600)))
                    .setEmission(Color::blue())
                    .setMaterial(Material().setReflective(0.5).setSpecular(0.5))));
    scene.geometries.addShared(
            std::make_shared<Sphere>(Sphere(camera.getPosition().add(camera.getvTo().scale(2000)), 80)
                                             .setEmission(Color::blue())
                                             .setMaterial(Material().setTransparent(1).setDiffusive(0.4).setSpecular(
                                                     0.3).setShininess(100))));


    scene.geometries.addShared(std::make_shared<Plane>(
            Plane(Point(0, -50, 0), Vector(0, 1, 0)).setEmission(Color(27, 55, 39).scale(0.85)).setMaterial(
                    Material().setDiffusive(0.5))));
    // ****geometries end

    // ****lights start
    for (int i = 1; i < howManyHouses * step/2; i += step) {
        scene.addStreetLamp(StreetLamp(Point(100, -50, -70).add(to.scale(houseSize/2)).add(to.scale(4 * houseSize * i)), 50,
                Color::red().add(Color::green()).scale(0.5), up, 1.25));
    }
    // ****lights end

    std::cout << "rendering..." << std::endl;
    ImageWriter imageWriter = ImageWriter("Mini-project1", 500, 500);
    camera.setImageWriter(imageWriter)
            //.setAntiAliasing(1)//
            .setRayTracer(RayTracer(scene)) //
            .renderImage() //
            .writeToImage(); //
}

void polygonTest(){
    Camera camera = Camera(Point(0, 0, -1000), Vector(0, 0, 1), Vector(0, 1, 0))
            .setVPSize(160, 160) // 16x9 scaled by 20
            .setVPDistance(1000);

    Scene scene = Scene("Tube");//.setBackground(Color(135, 206, 235));
    //.setAmbientLight(AmbientLight(Color(249,215,28),Double3(0.5)))

    scene.addGeometry(
            std::make_shared<Polygon>(Polygon(Point(50,50,0),Point(50,-50,0),Point(-50,-50,0), Point(-50,50,0))
                                           .setMaterial(Material().setDiffusive(0.5).setSpecular(0.5).setShininess(
                                                   20).setTransparent(0))
                                           .setEmission(Color::blue().reduce(2))));


    scene.addLight(std::make_shared<SpotLight>(SpotLight(Point(100, 100, 0), Vector(-1, -1, 1), Color(255, 0, 255))
                                                       .setNarrowBeam(10).setKl(0.00001).setKq(0.00001)));
    scene.addLight(std::make_shared<SpotLight>(SpotLight(Point(-100, -100, 0), Vector(1, 1, 1),Color::red().add(Color::blue()))
                                                       .setNarrowBeam(10).setKl(0.00001).setKq(0.00001)));

    ImageWriter imageWriter = ImageWriter("Polygon", 500, 500);
    camera.setImageWriter(imageWriter) //
            .setRayTracer(RayTracer(scene)) //
            .renderImage() //
            .writeToImage(); //

}

void street2() {
    Camera camera = Camera(Point(2000, 100, 450), Vector(-2, -0.1, -0.5), Vector(-0.1, 2, 0))
            .setVPSize(200, 200)
            .setVPDistance(1000);

    int howManyHouses = 400;
    double houseSize = 30;

    Scene scene = Scene("GroveStreet").setBackground(Color(2, 25, 60));

    // ****geometries start

    // *group House
    Vector up = Vector(0, 1, 0);
    Vector to = Vector(-1, 0, 0);
    Vector right = Vector(0,0,-1);

    Point housesCenter = Point(-30, -50, -140);

    double step = 2;
    //for (int i = 1; i < howManyHouses * step; i += (int)step) {
    //    scene.geometries.add(House(housesCenter.add(to.scale(houseSize * i)), houseSize, up, to.scale(-1)).house);
    //}
    scene.geometries.addShared(std::make_shared<Polygon>(
            Polygon(housesCenter.add(right.scale(-100)), housesCenter.add(right.scale(-300)),
                    housesCenter.add(right.scale(-300)).add(to.scale(600)),
                    housesCenter.add(right.scale(-100)).add(to.scale(600)))
                    .setEmission(Color::blue())
                    .setMaterial(Material().setReflective(0.5).setSpecular(0.5))));
    scene.geometries.addShared(
            std::make_shared<Sphere>(Sphere(camera.getPosition().add(camera.getvTo().scale(2000)), 80)
                                             .setEmission(Color::blue())
                                             .setMaterial(Material().setTransparent(1).setDiffusive(0.4).setSpecular(
                                                     0.3).setShininess(100))));


    scene.geometries.addShared(std::make_shared<Plane>(
            Plane(Point(0, -50, 0), Vector(0, 1, 0)).setEmission(Color(27, 55, 39).scale(0.85)).setMaterial(
                    Material().setDiffusive(0.5))));
    // ****geometries end

    // ****lights start
    for (int i = 1; i < 8; i += step) {
        scene.addStreetLamp(StreetLamp(Point(100, -50, -70).add(to.scale(houseSize/2)).add(to.scale(4 * houseSize * i)), 50,
                                       Color::red().add(Color::green()).scale(0.5), up, 1.25));
    }
    // ****lights end

    std::cout << "rendering..." << std::endl;
    ImageWriter imageWriter = ImageWriter("StreepLamp", 500, 500);
    camera.setImageWriter(imageWriter)
                    //.setAntiAliasing(1)//
            .setRayTracer(RayTracer(scene)) //
            .renderImage() //
            .writeToImage(); //
}

int main() {
    clock_t start = clock();

    //street();
    street2();
    tubeTest();
    polygonTest();
    gridTest();
    basicRenderTest();
    basicRenderMultiColorTest();
    LightsTests();
    reflectionTransparencyTests::trianglesTransparentSphere();
    reflectionTransparencyTests::twoSpheres();
    reflectionTransparencyTests::twoSpheresOnMirrors();

    clock_t end = clock();
    std::cout << end - start << std::endl;
    return 0;
}


void basicRenderMultiColorTest() {
    Scene scene = Scene("Test scene")//
            .setAmbientLight(AmbientLight(Color::white(), Point(0.2, 0.2, 0.2))); //



    Sphere sphere = Sphere(Point(0, 0, -100), 50);
    scene.geometries.addShared(std::make_shared<Sphere>(sphere));
    // up left

    //Pointers are bad idea
    Triangle triangle1 = Triangle(Point(-100, 0, -100), Point(0, 100, -100), Point(-100, 100, -100));
    triangle1.setEmission(Color::green());
    scene.geometries.addShared(std::make_shared<Triangle>(triangle1));


    // down left
    Triangle triangle2 = Triangle(Point(-100, 0, -100), Point(0, -100, -100), Point(-100, -100, -100));
    triangle2.setEmission(Color::red());
    scene.geometries.addShared(std::make_shared<Triangle>(triangle2));

    // down right
    Triangle triangle3 = Triangle(Point(100, 0, -100), Point(0, -100, -100), Point(100, -100, -100));
    triangle3.setEmission(Color::blue());
    scene.geometries.addShared(std::make_shared<Triangle>(triangle3));

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
    scene.geometries.addShared(std::make_shared<Sphere>(sphere));
    Triangle triangle1 = Triangle(Point(-100, 0, -100), Point(0, 100, -100), Point(-100, 100, -100)); // up
    scene.geometries.addShared(std::make_shared<Triangle>(triangle1));
    // left
    Triangle triangle2 = Triangle(Point(-100, 0, -100), Point(0, -100, -100), Point(-100, -100, -100)); // down left
    scene.geometries.addShared(std::make_shared<Triangle>(triangle2));

    Triangle triangle3 = Triangle(Point(100, 0, -100), Point(0, -100, -100), Point(100, -100, -100)); // down
    scene.geometries.addShared(std::make_shared<Triangle>(triangle3));

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