//
// Created by Ana on 4/24/2026.
//

#include "GammaCorrection.h"

GammaCorrection::GammaCorrection(double gamma) : gamma(gamma){};

void GammaCorrection::process(const Image &src, Image &dst) {
    dst = Image(src);  // Copy source - same size and initial contents

    // Apply linear transformation: dst(x,y) = alpha * src(x,y) + beta
    for (unsigned int y = 0; y < src.height(); y++) {
        for (unsigned int x = 0; x < src.width(); x++) {
            double srcPixel = src.at(x, y);
            double result = pow(srcPixel, gamma);
            dst.at(x, y) = static_cast<unsigned char>(result);
        }
    }
}
