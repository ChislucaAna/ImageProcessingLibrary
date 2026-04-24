//
// Created by Ana on 4/24/2026.
//

#ifndef IMAGEPROCESSINGLIBRARY_GAMMACORRECTION_H
#define IMAGEPROCESSINGLIBRARY_GAMMACORRECTION_H
#include "ImageProcessing.h"
#include <cmath>

class GammaCorrection : public ImageProcessing{
    double gamma;
public:
    GammaCorrection(double gamma);
    void process(const Image &src, Image &dst) override;
};


#endif //IMAGEPROCESSINGLIBRARY_GAMMACORRECTION_H