//
// Created by shoham on 7/17/22.
//

#include "copmlexShapes/Cube.h"

Cube::Cube(Point center, double length, Vector vUp, Vector vRight, Color color, Material material) {
    if (vUp.dotProduct(vRight) != 0) exit(-1);
    Vector vTo = vRight.crossProduct(vUp);
    double step = length / 2;

    Point frontCenter = center.add(vTo.scale(step));
    this->cube.addShared(std::make_shared<Polygon>(constructRectangle(frontCenter, vRight, vUp, length, length)
                           .setEmission(color).setMaterial(material)));

    Point backCenter = center.add(vTo.scale(-step));
    this->cube.addShared(std::make_shared<Polygon>(constructRectangle(backCenter, vRight, vUp, length, length)
                           .setEmission(color).setMaterial(material)));

    Point rightCenter = center.add(vRight.scale(step));
    this->cube.addShared(std::make_shared<Polygon>(constructRectangle(rightCenter, vTo, vUp, length, length)
                           .setEmission(color).setMaterial(material)));

    Point leftCenter = center.add(vRight.scale(-step));
    this->cube.addShared(std::make_shared<Polygon>(constructRectangle(leftCenter, vTo, vUp, length, length)
                           .setEmission(color).setMaterial(material)));

    Point topCenter = center.add(vUp.scale(step));
    this->cube.addShared(std::make_shared<Polygon>(constructRectangle(topCenter, vTo, vRight, length, length)
                           .setEmission(color).setMaterial(material)));

    Point bottomCenter = center.add(vUp.scale(-step));
    this->cube.addShared(std::make_shared<Polygon>(constructRectangle(bottomCenter, vTo, vRight, length, length)
                           .setEmission(color).setMaterial(material)));

}

Polygon Cube::constructRectangle(Point center, Vector vRight, Vector vUp, double height, double width) {
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
