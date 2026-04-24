//
// Created by Ana on 4/24/2026.
//

#ifndef IMAGEPROCESSINGLIBRARY_BRIGHTNESSANDCONTRAST_H
#define IMAGEPROCESSINGLIBRARY_BRIGHTNESSANDCONTRAST_H
#include "ImageProcessing.h"


class BrightnessAndContrast : public ImageProcessing{
    double alpha;
    double beta;
public:
    BrightnessAndContrast();
    BrightnessAndContrast(double alpha, double beta);
    void process(const Image& src, Image& dst) override;

};


#endif //IMAGEPROCESSINGLIBRARY_BRIGHTNESSANDCONTRAST_H