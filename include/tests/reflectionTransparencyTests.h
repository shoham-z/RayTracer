//
// Created by shoham on 6/23/22.
//

#ifndef RAYTRACER_REFLECTIONTRANSPARENCYTESTS_H
#define RAYTRACER_REFLECTIONTRANSPARENCYTESTS_H


class reflectionTransparencyTests {


    /**
     * Produce a picture of a sphere lighted by a spot light
     */
public:
    static void twoSpheres() {
        Scene scene = Scene("Test scene");
        Camera camera = Camera(Point(0, 0, 1000), Vector(0, 0, -1), Vector(0, 1, 0)) //
                .setVPSize(150, 150).setVPDistance(1000);

        scene.geometries.addShared(std::make_shared<Sphere>(
                Sphere(Point(0, 0, -50), 50).setEmission(Color::blue()) //
                        .setMaterial(
                                Material().setDiffusive(0.4).setSpecular(0.3).setShininess(100).setTransparent(0.3))));
        scene.geometries.addShared(std::make_shared<Sphere>(Sphere(Point(0, 0, -50), 25).setEmission(Color::red()) //
                                                                    .setMaterial(
                                                                            Material().setDiffusive(0.5).setSpecular(
                                                                                    0.5).setShininess(100))));
        scene.lights.push_back(std::make_shared<SpotLight>(
                SpotLight(Point(-100, -100, 500), Vector(-1, -1, -2), Color(1, .6, 0)) //
                        .setKl(0.0004).setKq(0.0000006)));

        camera.setImageWriter(ImageWriter("refractionTwoSpheres", 500, 500)) //
                .setRayTracer(RayTracer(scene)) //
                .renderImage() //
                .writeToImage();
    }

    /**
     * Produce a picture of a sphere lighted by a spot light
     */

    static void twoSpheresOnMirrors() {
        Scene scene = Scene("Test scene");
        Camera camera = Camera(Point(0, 0, 10000), Vector(0, 0, -1), Vector(0, 1, 0)) //
                .setVPSize(2500, 2500).setVPDistance(10000); //

        scene.setAmbientLight(AmbientLight(Color::white(), Point(0.1)));

        scene.geometries.addShared(std::make_shared<Sphere>(
                Sphere(Point(-950, -900, -1000), 400).setEmission(Color(0, 0, 1)) //
                        .setMaterial(
                                Material().setDiffusive(0.25).setSpecular(0.25).setShininess(20).setTransparent(0.5))));
        scene.geometries.addShared(
                std::make_shared<Sphere>(Sphere(Point(-950, -900, -1000), 200).setEmission(Color(100, 20, 20)) //
                                                 .setMaterial(
                                                         Material().setDiffusive(0.25).setSpecular(0.25).setShininess(
                                                                 20))));
        scene.geometries.addShared(std::make_shared<Triangle>(
                Triangle(Point(1500, -1500, -1500), Point(-1500, 1500, -1500), Point(670, 670, 3000)) //
                        .setEmission(Color(20, 20, 20)) //
                        .setMaterial(Material().setReflective(1))));
        scene.geometries.addShared(
                std::make_shared<Triangle>(Triangle(Point(1500, -1500, -1500), Point(-1500, 1500, -1500),
                                                    Point(-1500, -1500, -2000)) //
                                                   .setEmission(Color(20, 20, 20)) //
                                                   .setMaterial(Material().setReflective(0.5))));


        scene.lights.push_back(std::make_shared<SpotLight>(
                SpotLight(Point(-750, -750, -150), Vector(-1, -1, -4), Color(1020, 400, 400)) //
                        .setKl(0.00001).setKq(0.000005)));
        ImageWriter imageWriter = ImageWriter("reflectionTwoSpheresMirrored", 500, 500);
        camera.setImageWriter(imageWriter) //
                .setRayTracer(RayTracer(scene)) //
                .renderImage() //
                .writeToImage();
    }

    /**
     * Produce a picture of a two triangles lighted by a spot light with a partially
     * transparent Sphere producing partial shadow
     */
    static void trianglesTransparentSphere() {
        Scene scene = Scene("Test scene");
        Camera camera = Camera(Point(0, 0, 1000), Vector(0, 0, -1), Vector(0, 1, 0)) //
                .setVPSize(200, 200).setVPDistance(1000);

        scene.setAmbientLight(AmbientLight(Color::white(), Point(0.15)));

        scene.geometries.addShared(std::make_shared<Triangle>(
                Triangle(Point(-150, -150, -115), Point(150, -150, -135), Point(75, 75, -150)) //
                        .setMaterial(Material().setDiffusive(0.5).setSpecular(0.5).setShininess(60)))); //
        scene.geometries.addShared(std::make_shared<Triangle>(
                Triangle(Point(-150, -150, -115), Point(-70, 70, -140), Point(75, 75, -150)) //
                        .setMaterial(Material().setDiffusive(0.5).setSpecular(0.5).setShininess(60)))); //
        scene.geometries.addShared(std::make_shared<Sphere>(Sphere(Point(60, 50, -50), 30).setEmission(Color::blue()) //
                                                                    .setMaterial(
                                                                            Material().setDiffusive(0.2).setSpecular(
                                                                                    0.2).setShininess(
                                                                                    30).setTransparent(0.6))));

        scene.lights.push_back(
                std::make_shared<SpotLight>(SpotLight(Point(60, 50, 0), Vector(0, 0, -1), Color(700, 400, 400)) //
                                                    .setKl(4E-5).setKq(2E-7)));

        ImageWriter imageWriter = ImageWriter("refractionShadow", 600, 600);
        camera.setImageWriter(imageWriter) //
                .setRayTracer(RayTracer(scene)) //
                .renderImage() //
                .writeToImage();
    }

};


#endif //RAYTRACER_REFLECTIONTRANSPARENCYTESTS_H
