//
// Created by Ana on 4/24/2026.
//

#ifndef IMAGEPROCESSINGLIBRARY_RECTANGLE_H
#define IMAGEPROCESSINGLIBRARY_RECTANGLE_H

#include "Point.h"
class Rectangle {
    int x;
    int y;
    int width;
    int height;
    public:
    Rectangle();
    Rectangle(int x, int y, int width, int height);
    int getX();
    int getY();
    int getWidth();
    int getHeight();
    void setX(int x);
    void setY(int y);
    void setWidth(int width);
    void setHeight(int height);
    Rectangle operator+(const Point& other) const;
    Rectangle operator-(const Point& other) const;
    Rectangle operator&(const Rectangle& other) const;
    Rectangle operator|(const Rectangle& other) const;
};


#endif //IMAGEPROCESSINGLIBRARY_RECTANGLE_H