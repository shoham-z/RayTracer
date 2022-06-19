#include "include/Vector.h"
#include "include/Point.h"
#include "include/Ray.h"
#include "include/Sphere.h"
#include "include/Util.h"
#include "include/Camera.h"
#include "include/Geometries.h"
#include "CameraTests.h"
#include "sphereTests.h"

void gridTest() {
    Scene scene = Scene("Test scene")
            .setAmbientLight(AmbientLight(Color::red(), Point(1,1,1))) //
            .setBackground( Color::red());

    Camera camera =  Camera(Point::ZERO(),  Vector(0, 0, -1),  Vector(0, 1, 0)) //
    .setVPDistance(100) //
            .setVPSize(500, 500) //
            .setImageWriter( ImageWriter("grid test", 1000, 1000))
            .setRayTracer( RayTracer(scene));

    camera.renderImage();
    camera.printGrid(100, Color(255,255,0));
    camera.writeToImage();
 }

 void basicRenderTest(){
     Scene scene =  Scene("Test scene")//
     .setAmbientLight( AmbientLight( Color(255, 191, 191), //
                                        Point(1, 1, 1))) //
             .setBackground( Color(75, 127, 90));

     Sphere sphere = Sphere(Point(0, 0, -100), 50);
     scene.geometries.add(&sphere);
     Camera camera =  Camera(Point::ZERO(),  Vector(0, 0, -1),  Vector(0, 1, 0)) //

     .setVPDistance(100) //
             .setVPSize(500, 500) //
             .setImageWriter( ImageWriter("base render test", 1000, 1000))
             .setRayTracer( RayTracer(scene));

     camera.renderImage();
     camera.printGrid(100,  Color::blue().add(Color::green()));
     camera.writeToImage();
}
 int main(){
    testGetNormal();
    testConstructRay();
    testFindIntersections();
    gridTest();
    basicRenderTest();
    return 0;
}