//
// Created by Ana on 4/24/2026.
//

#ifndef IMAGEPROCESSINGLIBRARY_IMAGECONVOLUTION_H
#define IMAGEPROCESSINGLIBRARY_IMAGECONVOLUTION_H

#include "Image.h"

typedef unsigned char (*ScalingFunction)(double);

class ImageConvolution {
private:
    double** kernel;
    unsigned int kernelWidth;
    unsigned int kernelHeight;
    int kernelCenter;
    ScalingFunction scalingFunc;

public:
    ImageConvolution(double** kernel, unsigned int width, unsigned int height, ScalingFunction func);
    ~ImageConvolution();
    void process(const Image& src, Image& dst);
};


#endif //IMAGEPROCESSINGLIBRARY_IMAGECONVOLUTION_H