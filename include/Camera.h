//
// Created by shoham on 6/17/22.
//
#include "ImageWriter.h"
#include "RayTracer.h"
#include "Point.h"
#include "Vector.h"
#include "Ray.h"
#include "Color.h"

#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H


class Camera {
    Point position;
    Vector vTo;
    Vector vUp;
    Vector vRight;
    int vpHeight;
    int vpWidth;
    double distanceFromVp;
    ImageWriter imageWriter = ImageWriter("", 0, 0);
    RayTracer rayTracer = RayTracer(Scene(""));

public:
    Camera(Point position, Vector to, Vector up);

    Point getPosition();
    Vector getvTo();
    Vector getvUp();
    Vector getvRight();
    int getVpHeight();
    int getVpWidth();
    double getDistanceFromVp();


    Camera setImageWriter(ImageWriter imageWriter1);
    Camera setRayTracer(RayTracer rayTracer);
    Camera setVPSize(int height, int width);
    Camera setVPDistance(double distance);

    Ray constructRay(int nX, int nY, int j, int i);
    void renderImage();
    void printGrid(int interval, Color color);
    void writeToImage();

};


#endif //RAYTRACER_CAMERA_H
