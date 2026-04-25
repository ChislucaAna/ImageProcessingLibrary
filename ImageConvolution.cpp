//
// Created by Ana on 4/24/2026.
//

#include "ImageConvolution.h"

/*
*How it works for out of bound pixels when applying the kernel
  - Pixels within bounds are included in the convolution sum
  - Pixels outside bounds are simply skipped (treated as 0)
  - No extra memory, no complex logic - just straightforward
 */

ImageConvolution::ImageConvolution(double** kernel, unsigned int width, unsigned int height, ScalingFunction func)
    : kernelWidth(width), kernelHeight(height), scalingFunc(func) {

    kernelCenter = width / 2;

    // Allocate and copy kernel
    this->kernel = new double*[height];
    for (unsigned int i = 0; i < height; i++) {
        this->kernel[i] = new double[width];
        for (unsigned int j = 0; j < width; j++) {
            this->kernel[i][j] = kernel[i][j];
        }
    }
}

ImageConvolution::~ImageConvolution() {
    if (this->kernel != nullptr) {
        for (unsigned int i = 0; i < this->kernelHeight; i++) {
            delete[] this->kernel[i];
        }
        delete[] this->kernel;
    }
}

void ImageConvolution::process(const Image& src, Image& dst) {
    // Create output image with same dimensions
    dst = Image(src.width(), src.height());

    // Apply convolution at each pixel
    for (unsigned int y = 0; y < src.height(); y++) {
        for (unsigned int x = 0; x < src.width(); x++) {
            double sum = 0.0;

            // Apply kernel
            for (unsigned int v = 0; v < this->kernelHeight; v++) {
                for (unsigned int u = 0; u < this->kernelWidth; u++) {
                    // Calculate source coordinates
                    int srcX = x - u + this->kernelCenter;
                    int srcY = y - v + this->kernelCenter;

                    // Zero padding: treat out-of-bounds pixels as 0
                    if (srcX >= 0 && srcX < (int)src.width() && srcY >= 0 && srcY < (int)src.height()) {
                        double pixelValue = (double)src.at(srcX, srcY);
                        sum += this->kernel[v][u] * pixelValue;
                    }
                    // else: pixel is out of bounds, contributes 0 (zero padding)
                }
            }

            // Apply scaling function and store result
            dst.at(x, y) = this->scalingFunc(sum);
        }
    }
}