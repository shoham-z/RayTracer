//
// Created by shoham on 6/19/22.
//

#include "CameraTests.h"
#include "Vector.h"
#include "Point.h"
#include "Ray.h"
#include "Camera.h"

void testConstructRay() {
    Camera camera = Camera(Point::ZERO(), Vector(0, 0, -1), Vector(0, -1, 0)).setVPDistance(10);
    std::string badRay = "Bad ray";

    // ============ Equivalence Partitions Tests ==============
    // EP01: 4X4 Inside (1,1)
    assertEquals(Ray(Point::ZERO(), Vector(1, -1, -10)),
                 camera.setVPSize(8, 8).constructRay(4, 4, 1, 1), badRay);

    // =============== Boundary Values Tests ==================
    // BV01: 3X3 Center (1,1)
    assertEquals(Ray(Point::ZERO(), Vector(0, 0, -10)),
                 camera.setVPSize(6, 6).constructRay(3, 3, 1, 1), badRay);

    // BV02: 3X3 Center of Upper Side (0,1)
    assertEquals(Ray(Point::ZERO(), Vector(0, -2, -10)),
                 camera.setVPSize(6, 6).constructRay(3, 3, 1, 0), badRay);

    // BV03: 3X3 Center of Left Side (1,0)
    assertEquals(Ray(Point::ZERO(), Vector(2, 0, -10)),
                 camera.setVPSize(6, 6).constructRay(3, 3, 0, 1), badRay);

    // BV04: 3X3 Corner (0,0)
    assertEquals(Ray(Point::ZERO(), Vector(2, -2, -10)),
                 camera.setVPSize(6, 6).constructRay(3, 3, 0, 0), badRay);

    // BV05: 4X4 Corner (0,0)
    assertEquals(Ray(Point::ZERO(), Vector(3, -3, -10)),
                 camera.setVPSize(8, 8).constructRay(4, 4, 0, 0), badRay);

    // BV06: 4X4 Side (0,1)
    assertEquals(Ray(Point::ZERO(), Vector(1, -3, -10)),
                 camera.setVPSize(8, 8).constructRay(4, 4, 1, 0), badRay);
}
void assertEquals(Ray expected, Ray actual, const std::string& message) {
    if (expected == actual) return;
    std::cout << message << std::endl;
    exit(-1);
}