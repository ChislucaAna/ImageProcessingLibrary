//
// ShapeDrawing.cpp
// Implementation of shape drawing functions
//

#include "ShapeDrawing.h"
#include <cmath>

void ShapeDrawing::drawCircle(Image& img, Point center, int radius, unsigned char color) {
    int cx = center.GetX();
    int cy = center.GetY();

    // Iterate through bounding box
    for (int y = cy - radius; y <= cy + radius; y++) {
        for (int x = cx - radius; x <= cx + radius; x++) {
            // Check if point is within image bounds
            if (x >= 0 && x < (int)img.width() && y >= 0 && y < (int)img.height()) {
                // Calculate distance from center
                int dx = x - cx;
                int dy = y - cy;
                int distSquared = dx * dx + dy * dy;
                int radiusSquared = radius * radius;

                // Draw if on or very close to circle boundary (within 1 pixel)
                if (distSquared >= (radius - 1) * (radius - 1) && distSquared <= (radius + 1) * (radius + 1)) {
                    img.at(x, y) = color;
                }
            }
        }
    }
}

void ShapeDrawing::drawLine(Image& img, Point p1, Point p2, unsigned char color) {
    int x1 = p1.GetX();
    int y1 = p1.GetY();
    int x2 = p2.GetX();
    int y2 = p2.GetY();

    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    int x = x1;
    int y = y1;

    // Bresenham's line algorithm
    while (true) {
        // Draw pixel if within bounds
        if (x >= 0 && x < (int)img.width() && y >= 0 && y < (int)img.height()) {
            img.at(x, y) = color;
        }

        // Check if we've reached the end point
        if (x == x2 && y == y2) {
            break;
        }

        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x += sx;
        }
        if (e2 < dx) {
            err += dx;
            y += sy;
        }
    }
}

void ShapeDrawing::drawRectangle(Image& img, Rectangle r, unsigned char color) {
    int x = r.getX();
    int y = r.getY();
    int width = r.getWidth();
    int height = r.getHeight();

    // Create corner points
    Point topLeft(x, y);
    Point bottomRight(x + width - 1, y + height - 1);

    drawRectangle(img, topLeft, bottomRight, color);
}

void ShapeDrawing::drawRectangle(Image& img, Point tl, Point br, unsigned char color) {
    int x1 = tl.GetX();
    int y1 = tl.GetY();
    int x2 = br.GetX();
    int y2 = br.GetY();

    // Top edge
    drawLine(img, Point(x1, y1), Point(x2, y1), color);

    // Bottom edge
    drawLine(img, Point(x1, y2), Point(x2, y2), color);

    // Left edge
    drawLine(img, Point(x1, y1), Point(x1, y2), color);

    // Right edge
    drawLine(img, Point(x2, y1), Point(x2, y2), color);
}
