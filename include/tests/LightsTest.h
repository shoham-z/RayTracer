//
// Created by shoham on 6/21/22.
//

#ifndef RAYTRACER_LIGHTSTEST_H
#define RAYTRACER_LIGHTSTEST_H

#include "primitives/Point.h"
#include "primitives/Vector.h"
#include "primitives/Color.h"
#include "primitives/Material.h"
#include "renderer/Camera.h"
#include "renderer/Scene.h"
#include "renderer/RayTracer.h"
#include "renderer/ImageWriter.h"
#include "geometries/Sphere.h"
#include "geometries/Triangle.h"
#include "lights/DirectionalLight.h"
#include "lights/SpotLight.h"
#include "lights/PointLight.h"

class LightsTests {
public:
    Camera camera1 = Camera(Point(0, 0, 1000), Vector(0, 0, -1), Vector(0, 1, 0)) //
            .setVPSize(150, 150) //
            .setVPDistance(1000);
    Camera camera2 = Camera(Point(0, 0, 1000), Vector(0, 0, -1), Vector(0, 1, 0)) //
            .setVPSize(200, 200) //
            .setVPDistance(1000);

    Point p[4] = { // The Triangles' vertices:
            Point(-110, -110, -150), // the shared left-bottom
            Point(95, 100, -150), // the shared right-top
            Point(110, -110, -150), // the right-bottom
            Point(-75, 78, 100)}; // the left-top
    Point trPL = Point(30, 10, -100); // Triangles test Position of Light
    Point spPL = Point(-50, -50, 25); // Sphere test Position of Light
    Color trCL = Color(800, 500, 250); // Triangles test Color of Light
    Color spCL = Color(800, 500, 0); // Sphere test Color of Light
    Vector trDL = Vector(-2, -2, -2); // Triangles test Direction of Light
    Material material = Material().setDiffusive(0.5).setSpecular(0.5).setShininess(300);
    Triangle triangle1 = Triangle(p[0], p[1], p[2]);
    Triangle triangle2 = Triangle(p[0], p[1], p[3]);
    Sphere sphere = Sphere(Point(0, 0, -50), 50);

    Color purple = Color::blue().add(Color::red());

    LightsTests() {
        this->triangle1.setMaterial(material);
        this->triangle2.setMaterial(material);
        this->sphere.setEmission(Color::blue().reduce(2));
        this->sphere.setMaterial(Material().setDiffusive(0.5).setSpecular(0.5).setShininess(300));
        sphereDirectional();
        sphereMultipleLights();
        spherePoint();
        sphereSpot();
        sphereSpotSharp();
        trianglesDirectional();
        trianglesMultipleLights();
        trianglesPoint();
        trianglesSpot();
        trianglesSpotSharp();
    }

    /**
     * Produce a picture of a sphere lighted by a directional light
     */

    void sphereDirectional() {
        Scene scene1 = Scene("Test scene");
        scene1.geometries.add(&sphere);
        std::shared_ptr<DirectionalLight> light = std::make_shared<DirectionalLight>(
                DirectionalLight(Vector(1, 1, -0.5), spCL));
        scene1.lights.push_back(light);

        ImageWriter imageWriter = ImageWriter("lightSphereDirectional", 1, 1);
        camera1.setImageWriter(imageWriter) //
                .setRayTracer(RayTracer(scene1)) //
                .renderImage() //
                .writeToImage(); //
    }

    /**
     * Produce a picture of a sphere lighted by a point light
     */

    void spherePoint() {
        Scene scene1 = Scene("Test scene");

        scene1.geometries.add(&sphere);
        std::shared_ptr<PointLight> light = std::make_shared<PointLight>(
                PointLight(spPL, spCL).setKl(0.001).setKq(0.0002));
        scene1.lights.push_back(light);

        ImageWriter imageWriter = ImageWriter("lightSpherePoint", 500, 500);
        camera1.setImageWriter(imageWriter) //
                .setRayTracer(RayTracer(scene1)) //
                .renderImage() //
                .writeToImage(); //
    }


    /**
     * Produce a picture of a sphere lighted by a spot light
     */

    void sphereSpot() {
        Scene scene1 = Scene("Test scene");

        scene1.geometries.add(&sphere);
        std::shared_ptr<SpotLight> light = std::make_shared<SpotLight>(
                SpotLight(spPL, Vector(1, 1, -0.5), spCL).setKl(0.001).setKq(0.0001));

        scene1.lights.push_back(light);

        ImageWriter imageWriter = ImageWriter("lightSphereSpot", 500, 500);
        camera1.setImageWriter(imageWriter) //
                .setRayTracer(RayTracer(scene1)) //
                .renderImage() //
                .writeToImage(); //
    }

    /**
     * Produce a picture of a two triangles lighted by a directional light
     */

    void trianglesDirectional() {
        Scene scene2 = Scene("Test scene") //
                .setAmbientLight(AmbientLight(Color::white(), Point(0.15)));
        scene2.geometries.add(&triangle1);
        scene2.geometries.add(&triangle2);
        std::shared_ptr<DirectionalLight> light = std::make_shared<DirectionalLight>(DirectionalLight(trDL, trCL));
        scene2.lights.push_back(light);

        ImageWriter imageWriter = ImageWriter("lightTrianglesDirectional", 500, 500);
        camera2.setImageWriter(imageWriter) //
                .setRayTracer(RayTracer(scene2)) //
                .renderImage() //
                .writeToImage(); //
    }

    /**
     * Produce a picture of a two triangles lighted by a point light
     */

    void trianglesPoint() {
        Scene scene2 = Scene("Test scene") //
                .setAmbientLight(AmbientLight(Color::white(), Point(0.15)));
        scene2.geometries.add(&triangle1);
        scene2.geometries.add(&triangle2);
        std::shared_ptr<PointLight> light = std::make_shared<PointLight>(
                PointLight(trPL, trCL).setKl(0.001).setKq(0.0002));
        scene2.lights.push_back(light);

        ImageWriter imageWriter = ImageWriter("lightTrianglesPoint", 500, 500);
        camera2.setImageWriter(imageWriter) //
                .setRayTracer(RayTracer(scene2)) //
                .renderImage() //
                .writeToImage(); //
    }

    /**
     * Produce a picture of a two triangles lighted by a spot light
     */

    void trianglesSpot() {
        Scene scene2 = Scene("Test scene") //
                .setAmbientLight(AmbientLight(Color::white(), Point(0.15)));
        scene2.geometries.add(&triangle1);
        scene2.geometries.add(&triangle2);
        std::shared_ptr<SpotLight> light = std::make_shared<SpotLight>(
                SpotLight(trPL, trDL, trCL).setKl(0.001).setKq(0.0001));
        scene2.lights.push_back(light);

        ImageWriter imageWriter = ImageWriter("lightTrianglesSpot", 500, 500);
        camera2.setImageWriter(imageWriter) //
                .setRayTracer(RayTracer(scene2)) //
                .renderImage() //
                .writeToImage(); //
    }

    /**
     * Produce a picture of a sphere lighted by a narrow spot light
     */

    void sphereSpotSharp() {
        Scene scene1 = Scene("Test scene");

        scene1.geometries.add(&sphere);
        std::shared_ptr<SpotLight> light = std::make_shared<SpotLight>(
                SpotLight(spPL, Vector(1, 1, -0.5), spCL).setNarrowBeam(10).setKl(0.001).setKq(0.00004));
        scene1.lights.push_back(light);

        ImageWriter imageWriter = ImageWriter("lightSphereSpotSharp", 500, 500);
        camera1.setImageWriter(imageWriter) //
                .setRayTracer(RayTracer(scene1)) //
                .renderImage() //
                .writeToImage(); //
    }

    /**
     * Produce a picture of a two triangles lighted by a narrow spot light
     */

    void trianglesSpotSharp() {
        Scene scene2 = Scene("Test scene") //
                .setAmbientLight(AmbientLight(Color::white(), Point(0.15)));
        scene2.geometries.add(&triangle1);
        scene2.geometries.add(&triangle2);
        std::shared_ptr<SpotLight> light = std::make_shared<SpotLight>(
                SpotLight(trPL, trDL, trCL).setNarrowBeam(10).setKl(0.001).setKq(0.00004));
        scene2.lights.push_back(light);

        ImageWriter imageWriter = ImageWriter("lightTrianglesSpotSharp", 500, 500);
        camera2.setImageWriter(imageWriter) //
                .setRayTracer(RayTracer(scene2)) //
                .renderImage() //
                .writeToImage(); //
    }

    /**
     * Produce a picture of a sphere lighted by multiple light sources
     */

    void sphereMultipleLights() {
        Scene scene1 = Scene("Test scene");

        scene1.geometries.add(&sphere);
        std::shared_ptr<DirectionalLight> light = std::make_shared<DirectionalLight>(
                DirectionalLight(Vector(1, 1, -0.5), Color::red().scale(2)));
        scene1.lights.push_back(light);
        light = std::make_shared<DirectionalLight>(
                DirectionalLight(Vector(-1, -1, -0.5), Color::red().add(Color::green()).scale(2)));
        scene1.lights.push_back(light);
        std::shared_ptr<PointLight> light1 = std::make_shared<PointLight>(
                PointLight(Point(50, -50, 0), Color::blue().add(Color::green().scale(2))).setKl(
                        0.001).setKq(0.0002));
        scene1.lights.push_back(light1);


        ImageWriter imageWriter = ImageWriter("multipleLightSphere", 500, 500);
        camera1.setImageWriter(imageWriter) //
                .setRayTracer(RayTracer(scene1)) //
                .renderImage() //
                .writeToImage(); //
    }

    /**
     * Produce a picture of two triangles lighted by multiple light sources
     */

    void trianglesMultipleLights() {
        Scene scene2 = Scene("Test scene") //
                .setAmbientLight(AmbientLight(Color::white(), Point(0.15)));
        scene2.geometries.add(&triangle1);
        scene2.geometries.add(&triangle2);
        std::shared_ptr<PointLight> light = std::make_shared<PointLight>(
                PointLight(trPL, purple).setKl(0.001).setKq(0.0002));
        scene2.lights.push_back(light);
        light = std::make_shared<PointLight>(
                PointLight(Point(30, -60, -100), Color::green()).setKl(0.001).setKq(0.0002));
        scene2.lights.push_back(light);
        std::shared_ptr<DirectionalLight> light1 = std::make_shared<DirectionalLight>(
                DirectionalLight(trDL, Color::blue()));
        scene2.lights.push_back(light1);


        ImageWriter imageWriter = ImageWriter("multipleLightTriangles", 500, 500);
        camera2.setImageWriter(imageWriter) //
                .setRayTracer(RayTracer(scene2)) //
                .renderImage() //
                .writeToImage(); //
    }

    /**
     * Tests method for {@link lighting.LightSource#getDistance(Point)}
     */

    void testGetDistance() {
        SpotLight spotLight = SpotLight(spPL, Vector(1, 1, -0.5), spCL);
        PointLight pointLight = PointLight(trPL, trCL);
        DirectionalLight directionalLight = DirectionalLight(trDL, trCL);

        // ============== Equivalence Partitions Tests ==================
        // EP01: Testing spotlight.getDistance
        //assertEquals(75, spotLight.getDistance(Point::ZERO),
        //             "EP01: not working");


        // EP02: Testing point-light.getDistance
        //assertEquals(104.880884817, pointLight.getDistance(Point::ZERO), 0.00001,
        //             "EP02: not working");

        // EP02: Testing directional light.getDistance
        //assertEquals(std::numeric_limits<double>::max(), directionalLight.getDistance(Point::ZERO),
        //             "EP02: not working");

    }

};


#endif //RAYTRACER_LIGHTSTEST_H
