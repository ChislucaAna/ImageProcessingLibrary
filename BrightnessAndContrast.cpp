//
// Created by Ana on 4/24/2026.
//

#include "BrightnessAndContrast.h"

BrightnessAndContrast::BrightnessAndContrast() {
    this->alpha = 1;
    this->beta = 0;
}

BrightnessAndContrast::BrightnessAndContrast(double alpha, double beta) {
    this->alpha = alpha;
    this->beta = beta;
}

void BrightnessAndContrast::process(const Image& src, Image& dst) {
    dst = Image(src);  // Copy source - same size and initial contents

    // Apply linear transformation: dst(x,y) = alpha * src(x,y) + beta
    for (unsigned int y = 0; y < src.height(); y++) {
        for (unsigned int x = 0; x < src.width(); x++) {
            double srcPixel = src.at(x, y);
            double result = this->alpha * srcPixel + this->beta;

            // Clip result to [0, 255] range
            if (result < 0.0) {
                result = 0.0;
            } else if (result > 255.0) {
                result = 255.0;
            }

            dst.at(x, y) = static_cast<unsigned char>(result);
        }
    }
}
