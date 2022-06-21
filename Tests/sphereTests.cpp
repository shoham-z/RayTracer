//
// Created by shoham on 6/19/22.
//

#include "tests/sphereTests.h"
#include "primitives/Point.h"
#include "geometries/Sphere.h"

void testGetNormal() {
    // ============ Equivalence Partitions Tests ==============
    // EP01: There is a simple single test here - the point is in the sphere
    Sphere sphere = Sphere(Point(1, 0, 0), 5);
    Vector actual = sphere.getNormal(Point(6, 0, 0));
    Vector expected = Vector(1, 0, 0);
    if (!(actual == expected)) {
        std::cout << "ERROR: normal for sphere is not working" << std::endl;
        exit(-1);
    }
}

void testFindIntersections() {
    Sphere sphere = Sphere(Point(1, 0, 0), 1);

    // ============ Equivalence Partitions Tests ==============

    // EP01: Ray's line is outside the sphere (0 points)
    //assertNull(sphere.findIntersections(Ray(Point(-1, 0, 0), Vector(1, 1, 0))),
    //           "EP01: Ray's line out of sphere");

    // EP02: Ray starts before and crosses the sphere (2 points)
    Point p1 = Point(0, 0, 0);
    Point p2 = Point(2, 0, 0);
    std::list <Point> result = sphere.findIntersections(Ray(Point(-2, 0, 0),
                                                       Vector(1, 0, 0)));
    //assertEquals(2, result.size(), "EP02: Wrong number of points");
    //if (result.get(0).getX() > result.get(1).getX())
    //    result = List.of(result.get(1), result.get(0));
    //assertEquals(List.of(p1, p2), result, "EP02: Ray crosses sphere");
    result.clear();

    // EP03: Ray starts inside the sphere (1 point)
    result = sphere.findIntersections(Ray(Point(1, 0.5, 0),
                                          Vector(3, 1, 0)));
    //assertEquals(List.of(Point(1.6851646544245034, 0.7283882181415011, 0)), result, "EP03: Wrong intersections");

    // EP04: Ray starts after the sphere (0 points)
    result = sphere.findIntersections(Ray(Point(2, 1, 0),
                                          Vector(3, 1, 0)));
    //assertNull(result, "EP04: Wrong number of points");
    // ...

    // =============== Boundary Values Tests ==================

    // **** Group: Ray's line crosses the sphere (but not the center)
    // BV01: Ray starts at sphere and goes inside (1 points)
    result = sphere.findIntersections(Ray(Point(0.2, 0.6, 0),
                                          Vector(0, -0.5, 0)));
    //assertEquals(1, result.size(), "BV01: Wrong number of points");
    //assertEquals(List.of(Point(0.2, -0.6, 0)), result, "BV01: Ray crosses sphere");
    result.clear();

    // BV02: Ray starts at sphere and goes outside (0 points)
    result = sphere.findIntersections(Ray(Point(0.2, 0.6, 0),
                                          Vector(0, 1, 0)));
    //assertNull(result, "BV02: Wrong number of points");

    // **** Group: Ray's line goes through the center
    // BV03: Ray starts before the sphere (2 points)
    result = sphere.findIntersections(Ray(Point(1, 1.1, 0),
                                          Vector(0, -0.5, 0)));
    //assertEquals(2, result.size(), "BV03: Wrong number of points");
    //if (result.get(0).getX() > result.get(1).getX())
    //    result = List.of(result.get(1), result.get(0));
    //assertEquals(List.of(Point(1, 1, 0), Point(1, -1, 0)), result,
    //             "BV03: Ray crosses sphere");
    result.clear();

    // BV04: Ray starts at sphere and goes inside (1 points)

    result = sphere.findIntersections(Ray(Point(1, 1, 0),
                                          Vector(0, -0.5, 0)));
    //assertEquals(1, result.size(), "BV04: Wrong number of points");
    //assertEquals(List.of(Point(1, -1, 0)), result,
    //             "BV04: Ray crosses sphere");
    result.clear();

    // BV05: Ray starts inside (1 points)
    result = sphere.findIntersections(Ray(Point(1, 0.9, 0),
                                          Vector(0, -0.5, 0)));
    //assertEquals(1, result.size(), "BV05: Wrong number of points");
    //assertEquals(List.of(Point(1, -1, 0)), result,
    //             "BV05: Ray crosses sphere");
    result.clear();

    // BV06: Ray starts at the center (1 points)
    result = sphere.findIntersections(Ray(Point(1, 0, 0),
                                          Vector(0, -0.5, 0)));
    //assertEquals(1, result.size(), "BV06: Wrong number of points");
    //assertEquals(List.of(Point(1, -1, 0)), result,
    //             "BV06: Ray crosses sphere");
    result.clear();

    // BV07: Ray starts at sphere and goes outside (0 points)
    result = sphere.findIntersections(Ray(Point(1, 1, 0),
                                          Vector(0, 0.5, 0)));
    //assertNull(result, "BV07: Wrong number of points");

    // BV08: Ray starts after sphere (0 points)
    result = sphere.findIntersections(Ray(Point(1, 1.1, 0),
                                          Vector(0, 0.5, 0)));
    //assertNull(result, "BV08: Wrong number of points");


    // **** Group: Ray's line is tangent to the sphere (all tests 0 points)
    // BV09: Ray starts before the tangent point
    result = sphere.findIntersections(Ray(Point(2, 1, 0),
                                          Vector(0, -0.5, 0)));
    //assertNull(result, "BV09: Wrong number of points");


    // BV10: Ray starts at the tangent point
    result = sphere.findIntersections(Ray(Point(2, 0, 0),
                                          Vector(0, -0.5, 0)));
    //assertNull(result, "BV10: Wrong number of points");


    // BV11: Ray starts after the tangent point
    result = sphere.findIntersections(Ray(Point(2, -1, 0),
                                          Vector(0, -0.5, 0)));
    //assertNull(result, "BV11: Wrong number of points");


    // **** Group: Special cases
    // BV12: Ray's line is outside, ray is orthogonal to ray start to sphere's center line
    result = sphere.findIntersections(Ray(Point(3, 2, 0),
                                          Vector(0, -0.5, 0)));
    //assertNull(result, "BV12: Wrong number of points");
    int count = 0;
}