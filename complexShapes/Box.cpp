//
// Created by shoham on 7/17/22.
//

#include "copmlexShapes/Box.h"

Polygon Box::constructRectangle(Point center, Vector vRight, Vector vUp, double height, double width) {

    double stepUp = height / 2;
    double stepSide = width / 2;
    Point frontBottomCenter = center.add(vUp.scale(-stepUp));
    Point frontTopCenter = center.add(vUp.scale(stepUp));
    Point frontTopRight = frontTopCenter.add(vRight.scale(stepSide));
    Point frontTopLeft = frontTopCenter.add(vRight.scale(-stepSide));
    Point frontBottomRight = frontBottomCenter.add(vRight.scale(stepSide));
    Point frontBottomLeft = frontBottomCenter.add(vRight.scale(-stepSide));
    return {frontTopRight, frontTopLeft, frontBottomLeft, frontBottomRight};

}

Box::Box(Point center, double length, double width, double height, Vector vUp, Vector vRight, Color color,
         Material material) {
    if (vUp.dotProduct(vRight) != 0) exit(-1);
    Vector vTo = vRight.crossProduct(vUp);

    Point frontCenter = center.add(vTo.scale(length / 2));
    this->box.addShared(std::make_shared<Polygon>(constructRectangle(frontCenter, vRight, vUp, height, width)
                          .setEmission(color).setMaterial(material)));

    Point backCenter = center.add(vTo.scale(-length / 2));
    this->box.addShared(std::make_shared<Polygon>(constructRectangle(backCenter, vRight, vUp, height, width)
                          .setEmission(color).setMaterial(material)));

    Point rightCenter = center.add(vRight.scale(width / 2));
    this->box.addShared(std::make_shared<Polygon>(constructRectangle(rightCenter, vTo, vUp, height, length)
                          .setEmission(color).setMaterial(material)));

    Point leftCenter = center.add(vRight.scale(-width / 2));
    this->box.addShared(std::make_shared<Polygon>(constructRectangle(leftCenter, vTo, vUp, height, length)
                          .setEmission(color).setMaterial(material)));

    Point topCenter = center.add(vUp.scale(height / 2));
    this->box.addShared(std::make_shared<Polygon>(constructRectangle(topCenter, vTo, vRight, width, length)
                          .setEmission(color).setMaterial(material)));

    Point bottomCenter = center.add(vUp.scale(-height / 2));
    this->box.addShared(std::make_shared<Polygon>(constructRectangle(bottomCenter, vTo, vRight, width, length)
                          .setEmission(color).setMaterial(material)));

}
