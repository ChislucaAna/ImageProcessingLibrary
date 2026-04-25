# Image Processing Library

A C++20 library for loading, manipulating, and saving grayscale PGM images. Built as an OOP project, it demonstrates class design, operator overloading, inheritance, and manual memory management.

---

## Features

- Load and save ASCII PGM (P2) images
- Brightness and contrast adjustment
- Gamma correction
- Image convolution with arbitrary kernels (blur, sharpen, edge detection, etc.)
- Region of interest (ROI) extraction
- Drawing shapes (circle, line, rectangle) onto images
- Arithmetic operators on images (`+`, `-`, `*`)

---

## Project Structure

```
ImageProcessingLibrary/
├── examples/                  # Sample input PGM images
│   ├── barbara.ascii.pgm
│   ├── glassware_noisy.ascii.pgm
│   └── apollonian_gasket.ascii.pgm
├── output/                    # Generated output images (created at runtime)
├── Image.h / Image.cpp        # Core image class
├── ImageProcessing.h          # Abstract base class for processing operations
├── BrightnessAndContrast.h/cpp
├── GammaCorrection.h/cpp
├── ImageConvolution.h/cpp
├── ShapeDrawing.h/cpp
├── Point.h/cpp
├── Size.h/cpp
├── Rectangle.h/cpp
├── main.cpp                   # Demo program
└── CMakeLists.txt
```

---

## Building

Requires CMake 3.x and a C++20-compatible compiler.

```bash
cmake -S . -B cmake-build-debug
cmake --build cmake-build-debug
```

---

## Running

The executable must be run from the build directory so that relative paths resolve correctly:

```bash
cd cmake-build-debug
./ImageProcessingLibrary
```

Input images are read from `../examples/` and output images are written to `../output/`.

---

## Class Overview

### `Image`
The central class. Stores pixel data as a 2D array of `unsigned char`.

| Method | Description |
|---|---|
| `Image(w, h)` | Creates a blank image of given dimensions |
| `load(path)` | Reads an ASCII PGM file |
| `save(path)` | Writes an ASCII PGM file |
| `at(x, y)` | Returns a reference to a pixel |
| `row(y)` | Returns a pointer to a row |
| `getROI(dst, x, y, w, h)` | Copies a sub-region into `dst` |
| `release()` | Frees all allocated memory |
| `zeros(w, h)` / `ones(w, h)` | Static factory methods |
| `+`, `-`, `*` | Per-pixel arithmetic with clamping |

### `ImageProcessing` (abstract)
Base class for all processing operations. Subclasses implement:
```cpp
void process(const Image& src, Image& dst);
```

### `BrightnessAndContrast`
Applies the transform `dst = alpha * src + beta` with clamping to [0, 255].

| Parameter | Effect |
|---|---|
| `alpha > 1` | Increases contrast |
| `alpha < 1` | Decreases contrast |
| `beta > 0` | Increases brightness |
| `beta < 0` | Decreases brightness |

### `GammaCorrection`
Applies `dst = (src / 255)^gamma * 255`.

- `gamma < 1` — brightens the image
- `gamma > 1` — darkens the image

### `ImageConvolution`
Applies an arbitrary kernel via 2D convolution. Accepts a custom scaling function (`unsigned char (*)(double)`) to map the result back to pixel range.

```cpp
double kernel[3][3] = { {1/9.0, ...} };  // box blur
ImageConvolution conv(kernel, 3, 3, clipToRange);
conv.process(src, dst);
```

### `ShapeDrawing`
Static methods for drawing onto an image in-place.

```cpp
ShapeDrawing::drawCircle(img, Point(cx, cy), radius, color);
ShapeDrawing::drawLine(img, Point(x1, y1), Point(x2, y2), color);
ShapeDrawing::drawRectangle(img, Point(tl), Point(br), color);
```

### `Rectangle`
Supports translation (`+`/`-` with `Point`) and set operations:
- `&` — intersection of two rectangles
- `|` — bounding rectangle of two rectangles

---

## Output Files

After running the demo, the following files are written to the `output/` directory:

| File | Description |
|---|---|
| `output_barbara_bright.pgm` | Brightness increased (beta=+30) |
| `output_barbara_contrast.pgm` | Contrast enhanced (alpha=1.5) |
| `output_glassware_denoised.pgm` | 3x3 box blur applied |
| `output_barbara_edges.pgm` | Sobel X edge detection |
| `output_barbara_roi.pgm` | 200x200 region of interest |
| `output_barbara_annotated.pgm` | Circle, line, and rectangle drawn |
