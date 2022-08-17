//
// Created by shoham on 6/17/22.
//
#include "ImageWriter.h"
#include "RayTracer.h"
#include "primitives/Point.h"
#include "primitives/Vector.h"
#include "primitives/Ray.h"
#include "primitives/Color.h"

#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H

class Camera;
namespace pixel{
    void colorPixel(Camera *camera, int start, int end, int width, int height);
}

class Camera {
    Point position;
    Vector vTo;
    Vector vUp;
    Vector vRight;
    int vpHeight = 0;
    int vpWidth = 0;
    double distanceFromVp = 0;
    int threads = 1;
public:
    uint size = 1;
    int progress = 0;
    ImageWriter imageWriter = ImageWriter("", 0, 0);
    RayTracer rayTracer = RayTracer(Scene(""));

    Camera(Point position, Vector to, Vector up);

    Point getPosition();
    Vector getvTo();
    Vector getvUp();
    Vector getvRight();
    int getVpHeight() const;
    int getVpWidth() const;
    double getDistanceFromVp() const;


    Camera setImageWriter(ImageWriter imageWriter1);
    Camera setRayTracer(RayTracer rayTracer);
    Camera setVPSize(int height, int width);
    Camera setVPDistance(double distance);
    Camera setAntiAliasing(uint amount);
    Camera setThreads(int t);

    [[nodiscard]] std::list<Ray> constructRay(int nX, int nY, int j, int i, uint length) const;
    [[nodiscard]] std::list<Ray> constructRaysThroughGrid(double height, double width, Point source, Point gridCenter, Vector vUp,
                                                    Vector vRight, uint length) const;
    Camera renderImage();
    Camera printGrid(int interval, Color color);
    Camera writeToImage();

};


#endif //RAYTRACER_CAMERA_H
