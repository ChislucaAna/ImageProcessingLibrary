#include <iostream>
#include <filesystem>
#include "Image.h"
#include "Point.h"
#include "Rectangle.h"
#include "BrightnessAndContrast.h"
#include "ImageConvolution.h"
#include "ShapeDrawing.h"

unsigned char clipToRange(double value) {
    if (value < 0.0) return 0;
    if (value > 255.0) return 255;
    return (unsigned char)value;
}

int main() {
    std::filesystem::create_directories("../output");

    std::cout << "====================================\n";
    std::cout << "  Image Processing Library Demo\n";
    std::cout << "====================================\n\n";

    // ============ 1. LOAD EXAMPLE IMAGES ============
    std::cout << "1. LOADING EXAMPLE IMAGES\n";

    Image barbara;
    std::cout << "   Loading '../examples/barbara.ascii.pgm'...\n";
    if (barbara.load("../examples/barbara.ascii.pgm")) {
        std::cout << "   Loaded successfully! Size: " << barbara.width() << "x" << barbara.height() << "\n";
    } else {
        std::cout << "   Failed to load image. Make sure you're running from cmake-build-debug directory.\n";
    }

    Image noisy;
    std::cout << "   Loading '../examples/glassware_noisy.ascii.pgm'...\n";
    if (noisy.load("../examples/glassware_noisy.ascii.pgm")) {
        std::cout << "   Loaded successfully! Size: " << noisy.width() << "x" << noisy.height() << "\n";
    } else {
        std::cout << "   Failed to load image. Make sure you're running from cmake-build-debug directory.\n";
    }

    Image gasket;
    std::cout << "   Loading '../examples/apollonian_gasket.ascii.pgm'...\n";
    if (gasket.load("../examples/apollonian_gasket.ascii.pgm")) {
        std::cout << "   Loaded successfully! Size: " << gasket.width() << "x" << gasket.height() << "\n";
    } else {
        std::cout << "   Failed to load image. Make sure you're running from cmake-build-debug directory.\n";
    }
    std::cout << "\n";

    // ============ 2. PIXEL ACCESS ============
    std::cout << "2. PIXEL ACCESS ON LOADED IMAGE\n";
    std::cout << "   Reading pixel at (100, 100) from barbara: " << (int)barbara.at(100, 100) << "\n";
    std::cout << "   Reading pixel at (200, 200) from barbara: " << (int)barbara.at(200, 200) << "\n\n";

    // ============ 3. BRIGHTNESS AND CONTRAST ============
    std::cout << "3. BRIGHTNESS AND CONTRAST ADJUSTMENT\n";

    std::cout << "   Brightening barbara image (alpha=1.0, beta=30)...\n";
    Image barbaraBright;
    BrightnessAndContrast bc1(1.0, 30);
    bc1.process(barbara, barbaraBright);
    barbaraBright.save("../output/output_barbara_bright.pgm");
    std::cout << "   Saved to 'output_barbara_bright.pgm'\n";

    std::cout << "   Increasing contrast of barbara (alpha=1.5, beta=-20)...\n";
    Image barbaraContrast;
    BrightnessAndContrast bc2(1.5, -20);
    bc2.process(barbara, barbaraContrast);
    barbaraContrast.save("../output/output_barbara_contrast.pgm");
    std::cout << "   Saved to 'output_barbara_contrast.pgm'\n\n";

    // ============ 4. IMAGE CONVOLUTION (DENOISING) ============
    std::cout << "4. IMAGE CONVOLUTION (BLUR FILTER FOR DENOISING)\n";

    std::cout << "   Applying 3x3 blur filter to noisy image...\n";
    double blurKernel[3][3] = {
        {1.0/9.0, 1.0/9.0, 1.0/9.0},
        {1.0/9.0, 1.0/9.0, 1.0/9.0},
        {1.0/9.0, 1.0/9.0, 1.0/9.0}
    };

    double** kernel = new double*[3];
    for (int i = 0; i < 3; i++) {
        kernel[i] = new double[3];
        for (int j = 0; j < 3; j++) {
            kernel[i][j] = blurKernel[i][j];
        }
    }

    ImageConvolution convolver(kernel, 3, 3, clipToRange);
    Image denoised;
    convolver.process(noisy, denoised);
    denoised.save("../output/output_glassware_denoised.pgm");
    std::cout << "   Denoised image saved to 'output_glassware_denoised.pgm'\n\n";

    // ============ 5. APPLYING EDGE DETECTION KERNEL ============
    std::cout << "5. EDGE DETECTION (SOBEL FILTER)\n";

    std::cout << "   Applying Sobel edge detection kernel...\n";
    double sobelX[3][3] = {
        {-1.0, 0.0, 1.0},
        {-2.0, 0.0, 2.0},
        {-1.0, 0.0, 1.0}
    };

    double** edgeKernel = new double*[3];
    for (int i = 0; i < 3; i++) {
        edgeKernel[i] = new double[3];
        for (int j = 0; j < 3; j++) {
            edgeKernel[i][j] = sobelX[i][j];
        }
    }

    ImageConvolution edgeDetector(edgeKernel, 3, 3, clipToRange);
    Image edges;
    edgeDetector.process(barbara, edges);
    edges.save("../output/output_barbara_edges.pgm");
    std::cout << "   Edge-detected image saved to 'output_barbara_edges.pgm'\n\n";

    // ============ 6. REGION OF INTEREST EXTRACTION ============
    std::cout << "6. REGION OF INTEREST (ROI) EXTRACTION\n";

    if (barbara.width() > 300 && barbara.height() > 300) {
        std::cout << "   Extracting 200x200 ROI from (100, 100) of barbara...\n";
        Image roi;
        if (barbara.getROI(roi, 100, 100, 200, 200)) {
            std::cout << "   ROI extracted: " << roi.width() << "x" << roi.height() << "\n";
            roi.save("../output/output_barbara_roi.pgm");
            std::cout << "   ROI saved to 'output_barbara_roi.pgm'\n";
        }
    }
    std::cout << "\n";

    // ============ 7. DRAWING SHAPES ON IMAGE ============
    std::cout << "7. DRAWING SHAPES ON LOADED IMAGE\n";

    Image annotated = barbara;

    std::cout << "   Drawing a circle at (512, 256) with radius 30...\n";
    ShapeDrawing::drawCircle(annotated, Point(512, 256), 30, 255);

    std::cout << "   Drawing a line from (100, 100) to (400, 400)...\n";
    ShapeDrawing::drawLine(annotated, Point(100, 100), Point(400, 400), 200);

    std::cout << "   Drawing a rectangle from (50, 50) to (300, 300)...\n";
    ShapeDrawing::drawRectangle(annotated, Point(50, 50), Point(300, 300), 180);

    annotated.save("../output/output_barbara_annotated.pgm");
    std::cout << "   Annotated image saved to 'output_barbara_annotated.pgm'\n\n";

    // ============ 8. ROW-WISE PROCESSING ============
    std::cout << "8. ROW-WISE PROCESSING\n";
    std::cout << "   Accessing row data for efficient processing...\n";
    unsigned char* row = barbara.row(100);
    if (row != nullptr) {
        std::cout << "   Row 100 accessed successfully\n";
        std::cout << "   Can process " << barbara.width() << " pixels in this row\n";
    }
    std::cout << "\n";

    // ============ 9. IMAGE PROPERTIES AND STATISTICS ============
    std::cout << "9. IMAGE PROPERTIES\n";
    std::cout << "   Barbara - Width: " << barbara.width() << ", Height: " << barbara.height() << "\n";
    std::cout << "   Barbara - Is Empty: " << (barbara.isEmpty() ? "Yes" : "No") << "\n";
    std::cout << "   Barbara - Size Object: " << barbara.size().GetWidth() << "x" << barbara.size().GetHeight() << "\n";
    std::cout << "   Noisy  - Width: " << noisy.width() << ", Height: " << noisy.height() << "\n";
    std::cout << "   Gasket - Width: " << gasket.width() << ", Height: " << gasket.height() << "\n\n";

    // Clean up
    for (int i = 0; i < 3; i++) {
        delete[] kernel[i];
        delete[] edgeKernel[i];
    }
    delete[] kernel;
    delete[] edgeKernel;

    std::cout << "====================================\n";
    std::cout << "  Demo Complete!\n";
    std::cout << "====================================\n";
    std::cout << "Generated output files:\n";
    std::cout << "  - output/output_barbara_bright.pgm     (Brightness adjusted)\n";
    std::cout << "  - output/output_barbara_contrast.pgm   (Contrast enhanced)\n";
    std::cout << "  - output/output_glassware_denoised.pgm (Blur filter applied)\n";
    std::cout << "  - output/output_barbara_edges.pgm      (Edge detection)\n";
    std::cout << "  - output/output_barbara_roi.pgm        (Region of Interest)\n";
    std::cout << "  - output/output_barbara_annotated.pgm  (Shapes drawn)\n";
    std::cout << "====================================\n";

    return 0;
}