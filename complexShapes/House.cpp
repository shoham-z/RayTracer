//
// Created by shoham on 7/17/22.
//

#include "copmlexShapes/House.h"

House::House(Point baseBottom, double height, Vector up, Vector right) {
    if (up.dotProduct(right) != 0) exit(-1);
    Material material = Material().setDiffusive(0.05).setSpecular(0);
    Vector to = right.crossProduct(up).normalize();
    right = right.normalize();
    up = up.normalize();


    Point frontBottomCenter = baseBottom.add(to.scale(height / 2)).add(to.scale(height/100));

    double doorWidth = height * 3 / 10;
    double doorHeight = height * 3 / 5;

    Point doorBottomRight = frontBottomCenter.add(right.scale(doorWidth / 2));
    Point doorBottomLeft = frontBottomCenter.add(right.scale(-doorWidth / 2));
    Point doorTopRight = doorBottomRight.add(up.scale(doorHeight));
    Point doorTopLeft = doorBottomLeft.add(up.scale(doorHeight));
    std::vector<Point> edges;
    edges.emplace_back(doorTopRight);
    edges.emplace_back(doorTopLeft);
    edges.emplace_back(doorBottomLeft);
    edges.emplace_back(doorBottomRight);

    Polygon door = Polygon(edges).setMaterial(
            material).setEmission(Color(1, .24, .24));


    Pyramid roof = Pyramid(baseBottom.add(up.scale(height)), height, height, to, up, Color(1, 0.45121951219, 0.45121951219), material);

    Cube body = Cube(baseBottom.add(up.scale(height / 2)), height, up, right, Color(0.98418972332, 1,0.7233201581), material);

    this->house.add(roof.pyramid);
    this->house.add(body.cube);
    this->house.addShared(std::make_shared<Polygon>(door));
}
