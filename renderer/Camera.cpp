//
// Created by shoham on 6/17/22.
//

#include "renderer/Camera.h"

#include <utility>
#include <thread>

Camera Camera::setImageWriter(ImageWriter imageWriter1) {
    this->imageWriter = std::move(imageWriter1);
    return *this;
}

Camera Camera::setRayTracer(RayTracer raytracer) {
    this->rayTracer = std::move(raytracer);
    return *this;
}

Camera::Camera(Point position, Vector to, Vector up)
        : position(position), vTo(to.normalize()), vUp(up.normalize()), vRight(to.crossProduct(up).normalize()) {
    if (to.dotProduct(up) != 0) {
        exit(-1);
    }
}

Camera Camera::setVPSize(int height, int width) {
    this->vpHeight = height;
    this->vpWidth = width;
    return *this;
}

Camera Camera::setVPDistance(double distance) {
    this->distanceFromVp = distance;
    return *this;
}

Camera Camera::setAntiAliasing(int amount) {
    this->size = amount;
    return *this;
}

std::list<Ray> Camera::constructRay(int nX, int nY, int j, int i) const {
    Point pIJ = this->position.add(this->vTo.scale(this->distanceFromVp));
    double sizeOfX = (double) this->vpWidth / nX;
    double sizeOfY = (double) this->vpHeight / nY;

    double xJ = (j - ((nX - 1) / (double) 2)) * sizeOfX;
    double yI = (((nY - 1) / (double) 2) - i) * sizeOfY;
    if (xJ != 0) pIJ = pIJ.add(vRight.scale(xJ));
    if (yI != 0) pIJ = pIJ.add(vUp.scale(yI));

    return this->constructRaysThroughGrid(sizeOfY, sizeOfX, this->position, pIJ, this->vUp, this->vRight);
}

std::list<Ray> Camera::constructRaysThroughGrid(double height, double width, Point source, Point gridCenter, Vector vUp,
                                                Vector vRight) const {
    std::list<Ray> rays;
    double xJ;
    double yI = height / (2 * this->size) - (height / 2);
    Point destination;
    for (int i = 0; i < this->size; i++) {
        xJ = width / (2 * this->size) - (width / 2);
        for (int j = 0; j < this->size; j++) {
            destination = gridCenter;
            if (xJ != 0) destination = destination.add(vRight.scale(xJ));
            if (yI != 0) destination = destination.add(vUp.scale(yI));
            rays.emplace_back(Ray(source, destination.subtract(source)));
            xJ = (xJ + width / this->size);
            if (xJ > (width / 2))
                xJ = -width / (2 * this->size);
        }
        yI = yI + height / this->size;
        if (yI > (height / 2))
            yI = -height / (2 * this->size);
    }
    return rays;
}

Camera Camera::renderImage() {
    if (this->vpHeight <= 0 || this->vpWidth <= 0 || this->distanceFromVp <= 0) {
        exit(-1);
    }
    int yPixels = this->imageWriter.getHeight();
    int xPixels = this->imageWriter.getWidth();
    std::vector<std::thread> threads;

    for (int i = 0; i < this->threads; i++) {
            threads.emplace_back(pixel::colorPixel, this, i* (yPixels/this->threads),(i+1)* (yPixels/this->threads) , xPixels, yPixels);

    }
    for (auto & thread : threads)
        thread.join();


    return *this;
}

void pixel::colorPixel(Camera *camera, int start, int end, int width, int height) {

    for (int i = start; i < end; i++) {
        for (int j = 0; j < width; j++) {
            camera->progress++;
            if(camera->progress % 500 == 0) {std::cout<< camera->progress * 100 / (double)(width*height) << "%" << std::endl; camera->writeToImage();}
            std::list<Ray> rays = camera->constructRay( width, height, j, i);
            for (Ray ray: rays) {
                camera->imageWriter.writePixel(i, j,  camera->rayTracer.traceRay(ray));
            }
        }
    }

}

Point Camera::getPosition() {
    return this->position;
}

Vector Camera::getvTo() {
    return this->vTo;
}

Vector Camera::getvUp() {
    return this->vUp;
}

Vector Camera::getvRight() {
    return this->vRight;
}

int Camera::getVpHeight() {
    return this->vpHeight;
}

int Camera::getVpWidth() {
    return this->vpWidth;
}

double Camera::getDistanceFromVp() {
    return this->distanceFromVp;
}

Camera Camera::printGrid(int interval, Color color) {
    for (int i = 0; i < this->imageWriter.getWidth(); i++) {
        for (int j = 0; j < this->imageWriter.getHeight(); j++) {
            if (i % interval == 0 || j % interval == 0) this->imageWriter.writePixel(i, j, color);
        }
    }
    return *this;
}

Camera Camera::writeToImage() {
    this->imageWriter.writeToImage();
    return *this;
}

Camera Camera::setThreads(int t) {
    this->threads = t;
    return *this;
}
