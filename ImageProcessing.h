//
// Created by Ana on 4/24/2026.
//

#ifndef IMAGEPROCESSINGLIBRARY_IMAGEPROCESSING_H
#define IMAGEPROCESSINGLIBRARY_IMAGEPROCESSING_H
#include "Image.h"


class ImageProcessing {
public:
    virtual ~ImageProcessing() = default;

    virtual void process(const Image& src, Image& dst) =0;
};


#endif //IMAGEPROCESSINGLIBRARY_IMAGEPROCESSING_H