//
// Created by shoham on 6/17/22.
//

#include "renderer/Camera.h"
#include "geometries/Triangle.h"
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

Camera Camera::setAntiAliasing(uint amount) {
    this->size = amount;
    return *this;
}

std::list<Ray> Camera::constructRay(int nX, int nY, int j, int i, uint length) const {
    Point pIJ = this->position.add(this->vTo.scale(this->distanceFromVp));
    double sizeOfX = (double) this->vpWidth / nX;
    double sizeOfY = (double) this->vpHeight / nY;

    double xJ = (j - ((nX - 1) / (double) 2)) * sizeOfX;
    double yI = (((nY - 1) / (double) 2) - i) * sizeOfY;
    if (xJ != 0) pIJ = pIJ.add(vRight.scale(xJ));
    if (yI != 0) pIJ = pIJ.add(vUp.scale(yI));

    return this->constructRaysThroughGrid(sizeOfY, sizeOfX, this->position, pIJ, this->vUp, this->vRight, length);
}

std::list<Ray> Camera::constructRaysThroughGrid(double height, double width, Point source, Point gridCenter, Vector vUp,
                                                Vector vRight, uint length) const {
    std::list<Ray> rays;
    double xJ;
    double yI = height / (2 * length) - (height / 2);
    Point destination;
    for (int i = 0; i < length; i++) {
        xJ = width / (2 * length) - (width / 2);
        for (int j = 0; j < length; j++) {
            destination = gridCenter;
            if (xJ != 0) destination = destination.add(vRight.scale(xJ));
            if (yI != 0) destination = destination.add(vUp.scale(yI));
            rays.emplace_back(Ray(source, destination.subtract(source)));
            xJ = (xJ + width / length);
            if (xJ > (width / 2))
                xJ = -width / (2 * length);
        }
        yI = yI + height / length;
        if (yI > (height / 2))
            yI = -height / (2 * length);
    }
    return rays;
}

Camera Camera::raytraceImage() {
    if (this->vpHeight <= 0 || this->vpWidth <= 0 || this->distanceFromVp <= 0) {
        exit(-1);
    }
    int yPixels = this->imageWriter.getHeight();
    int xPixels = this->imageWriter.getWidth();
    std::vector<std::thread> threads;

    for (int i = 0; i < this->threads; i++) {
        threads.emplace_back(pixel::colorPixel, this, i * (yPixels / this->threads),
                             (i + 1) * (yPixels / this->threads), xPixels, yPixels);

    }
    for (auto &thread: threads)
        thread.join();


    return *this;
}

void pixel::colorPixel(Camera *camera, int start, int end, int width, int height) {
    for (int i = start; i < end; i++) {
        for (int j = 0; j < width; j++) {
            camera->progress++;
            if (camera->progress % 500 == 0) {
                std::cout << camera->progress * 100 / (double) (width * height) << "%" << std::endl;
                camera->writeToImage();
            }

            Color color{};
            if (camera->size == 1) {
                camera->imageWriter.writePixel(i, j, camera->rayTracer.traceRay(
                        camera->constructRay(width, height, j, i, 1).front()));
            } else {
                for (int AASize = 2; AASize <= camera->size; ++AASize) {

                    std::vector<Color> colors;

                    std::list<Ray> rays = camera->constructRay(width, height, j, i, AASize);
                    uint index = 0;
                    for (Ray ray: rays) {
                        colors.emplace_back(camera->rayTracer.traceRay(ray));
                        index++;
                    }
                    if (Color::equal(colors) || AASize == camera->size) {
                        color = Color::average(colors);
                        break;
                    }
                }
                camera->imageWriter.writePixel(i, j, color);
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

int Camera::getVpHeight() const {
    return this->vpHeight;
}

int Camera::getVpWidth() const {
    return this->vpWidth;
}

double Camera::getDistanceFromVp() const {
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

Camera Camera::rasterizeImage() {
// rasterization algorithm

    // iterate over all the triangles
    // get the closest triangles to the camera
    // color the pixel in that color

    // take camera vector, and add zero in the quaternion's dimension
    // and we have (x,y,z,w)
    // x' = (1-2(y*y+z*z), 2(x*y+w*z)  , 2(x*z-w*y)  ) = (m1,m2,m3)
    // y' = (2(x*y-w*z)  , 1-2(x*x+z*z), 2(x*w+z*y)  ) = (m4,m5,m6)
    // z' = (2(w*y+x*z)  , 2(y*z-w*x)  , 1-2(x*x+y*y)) = (m7,m8,m9)

    // angleZ = arctan(m2/m1) = arctan(2(x*y+w*z)/1-2(y*y+z*z))
    // angleY = arcsin(-m3) = arcsin(-2(x*z-w*y))
    // angleX = arctan(m6/m9) = arctan(2(x*w+z*y)/1-2(x*x+y*y))


    // optimization: get the bounding box and
    for (auto t: this->rasterizer.getScene().geometries.geometries) {
        // STEP 1: project vertices of the triangle using perspective projection
        auto triangle = rasterizer.getPerspectiveProjectedTriangles();
        Vec2f v0 = perspectiveProject(triangle.v0);
        Vec2f v1 = perspectiveProject(triangle.v1);
        Vec2f v2 = perspectiveProject(triangle.v2);
        for (each pixel in image) {
            // STEP 2: is this pixel contained in the projected image of the triangle?
            if (pixelContainedIn2DTriangle(v0, v1, v2, x, y)) {
                image(x, y) = triangle[i].color;
            }
        }
    }
    return *this;
}
