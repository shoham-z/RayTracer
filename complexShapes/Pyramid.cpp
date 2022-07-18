//
// Created by shoham on 7/17/22.
//

#include "copmlexShapes/Pyramid.h"

Pyramid::Pyramid(Point bottomCenter, double height, double width, Vector vTo, Vector vUp, Color color,
                 Material material) {
    if (vTo.dotProduct(vUp) != 0) exit(-1);
    Vector vRight = vTo.crossProduct(vUp).normalize();
    Point top = bottomCenter.add(vUp.normalize().scale(height));
    Point frontCenter = bottomCenter.add(vTo.normalize().scale(width / 2));
    Point leftFront = frontCenter.add(vRight.normalize().scale(-width / 2));
    Point rightFront = frontCenter.add(vRight.normalize().scale(width / 2));
    Point backCenter = bottomCenter.add(vTo.normalize().scale(-width / 2));
    Point leftBack = backCenter.add(vRight.normalize().scale(-width / 2));
    Point rightBack = backCenter.add(vRight.normalize().scale(width / 2));

    Triangle front = Triangle(leftFront, rightFront, top).setEmission(color).setMaterial(material);
    Triangle back = Triangle(leftBack, rightBack, top).setEmission(color).setMaterial(material);
    Triangle right = Triangle(rightBack, rightFront, top).setEmission(color).setMaterial(material);
    Triangle left = Triangle(leftFront, leftBack, top).setEmission(color).setMaterial(material);
    Polygon bottom = Polygon(leftBack, leftFront, rightFront, rightBack).setEmission(color).setMaterial(material);

    this->pyramid.addShared(std::make_shared<Triangle>(front));
    this->pyramid.addShared(std::make_shared<Triangle>(back));
    this->pyramid.addShared(std::make_shared<Triangle>(right));
    this->pyramid.addShared(std::make_shared<Triangle>(left));
    this->pyramid.addShared(std::make_shared<Polygon>(bottom));
}
