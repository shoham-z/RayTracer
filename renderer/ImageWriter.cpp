//
// Created by shoham on 6/17/22.
//

#include "renderer/ImageWriter.h"

#include <utility>

ImageWriter::ImageWriter(std::string imageName, int nX, int nY) {
    this->imageName = std::move(imageName);
    this->width = nX;
    this->height = nY;

    this->image = new Color[nX * nY];
}

int ImageWriter::getHeight() const {
    return this->height;
}

int ImageWriter::getWidth() const {
    return this->width;
}

void ImageWriter::writePixel(int xIndex, int yIndex, Color color) {
    int tmp = xIndex * this->height + yIndex;
    this->image[tmp] = color;
}

void ImageWriter::writeToImage() {
    std::ofstream ofs("../images/" + this->imageName + ".ppm", std::ios_base::out | std::ios_base::binary);

    ofs << "P6" << std::endl << this->width << ' ' << this->height << std::endl << "255" << std::endl;

    Color color;
    for (int j = 0; j < this->height; ++j)
        for (int i = 0; i < this->width; ++i) {
            int index = i + j * this->height;
            color = this->image[index];
            ofs << (char) (color.getR()*255)
                << (char) (color.getG()*255)
                << (char) (color.getB()*255);       // red, green, blue
        }

    ofs.close();

}