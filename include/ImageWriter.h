//
// Created by shoham on 6/17/22.
//
#include <fstream>
#include <filesystem>
#include "Vector.h"
#include "Color.h"


#ifndef RAYTRACER_IMAGEWRITER_H
#define RAYTRACER_IMAGEWRITER_H


class ImageWriter {
    int height, width;
    Color** image;
    std::string imageName;
    std::string FOLDER_PATH;


public:
    ImageWriter(std::string imageName, int nX, int nY);
    int getHeight();
    int getWidth();
    void writeToImage();
    void writePixel(int xIndex, int yIndex, Color color);
};


#endif //RAYTRACER_IMAGEWRITER_H
