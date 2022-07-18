//
// Created by shoham on 6/17/22.
//

#include "renderer/Camera.h"

Camera Camera::setImageWriter(ImageWriter imageWriter1) {
    this->imageWriter = imageWriter1;
    return *this;
}

Camera Camera::setRayTracer(RayTracer raytracer) {
    this->rayTracer = raytracer;
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

std::list<Ray> Camera::constructRay(int nX, int nY, int j, int i) {
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
    double level = 0;
    int yPixels = this->imageWriter.getHeight();
    int xPixels = this->imageWriter.getWidth();
    for (int i = 0; i < xPixels; i++) {
        for (int j = 0; j < yPixels; j++)
        {
            if(j % 100 == 0) std::cout<< level * 100 / (double)(yPixels*xPixels) << "%" <<std::endl;
            std::list<Ray> rays = this->constructRay(xPixels, yPixels, j, i);
            for(Ray ray : rays){
                this->imageWriter.writePixel(i, j, this->rayTracer.traceRay(ray));
            }
            level++;
        }

    }
    return *this;
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
