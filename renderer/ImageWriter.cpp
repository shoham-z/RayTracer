//
// Created by shoham on 6/17/22.
//

#include "ImageWriter.h"

ImageWriter::ImageWriter(std::string imageName, int nX, int nY) {
    this->imageName = imageName;
    this->width = nX;
    this->height = nY;
    this->FOLDER_PATH = "/home/shoham/CLionProjects/RayTracer/images/";

    this->image = new Color*[nX * nY];

}

int ImageWriter::getHeight() {
    return this->height;
}

int ImageWriter::getWidth() {
    return this->width;
}

void ImageWriter::writePixel(int xIndex, int yIndex, Color color) {
    int tmp = xIndex+this->height*yIndex;
    this->image[tmp] = &color;
}

void ImageWriter::writeToImage() {
    // here the color array is still fine
    std::ofstream ofs(this->FOLDER_PATH + this->imageName + "first.ppm", std::ios_base::out | std::ios_base::binary);
    // here the color array is messed up - CREATE DATA STRUCTURE ???

    ofs << "P6" << std::endl << this->width << ' ' << this->height << std::endl << "255" << std::endl;

    Color color = Color::red().add(Color::blue());
    for (int j = 0; j < this->height; ++j)
        for (int i = 0; i < this->width; ++i) {
            int index = i + j * this->height;
            Color color = *this->image[index];
            if(index % 100==0){
                int b = 0;
            }
            ofs << (char) (color.getR())
                << (char) (color.getG())
                << (char) (color.getB());       // red, green, blue
            //std::cout << j << "," << i << std::endl;
        }

    ofs.close();

}