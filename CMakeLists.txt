cmake_minimum_required(VERSION 4.1)
project(ImageProcessingLibrary)

set(CMAKE_CXX_STANDARD 20)

add_executable(ImageProcessingLibrary main.cpp
        Size.cpp
        Size.h
        Point.cpp
        Point.h
        Rectangle.cpp
        Rectangle.h
        Image.cpp
        Image.h
        ImageProcessing.cpp
        ImageProcessing.h
        BrightnessAndContrast.cpp
        BrightnessAndContrast.h
        GammaCorrection.cpp
        GammaCorrection.h
        ImageConvolution.cpp
        ImageConvolution.h
        ShapeDrawing.cpp
)
