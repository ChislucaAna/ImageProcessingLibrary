//
// Created by Ana on 4/24/2026.
//

#include "Rectangle.h"

// Default constructor -> inline this time :D
Rectangle::Rectangle()
    : x(0), y(0), width(0), height(0) {}

// Parameterized constructor
Rectangle::Rectangle(int x, int y, int width, int height)
    : x(x), y(y), width(width), height(height) {}

// Getters
int Rectangle::getX() {
    return x;
}

int Rectangle::getY() {
    return y;
}

int Rectangle::getWidth() {
    return width;
}

int Rectangle::getHeight() {
    return height;
}

// Setters
void Rectangle::setX(int x) {
    this->x = x;
}

void Rectangle::setY(int y) {
    this->y = y;
}

void Rectangle::setWidth(int width) {
    this->width = width;
}

void Rectangle::setHeight(int height) {
    this->height = height;
}

Rectangle Rectangle::operator+(const Point& other) const {
    return Rectangle(this->x+other.GetX(),this->y+other.GetY(),width,height);
}

Rectangle Rectangle::operator-(const Point& other) const {
    return Rectangle(this->x-other.GetX(),this->y-other.GetY(),width,height);
}

Rectangle Rectangle::operator&(const Rectangle& other) const {
    int left = (this->x > other.x) ? this->x : other.x;
    int top = (this->y > other.y) ? this->y : other.y;
    int right = (this->x + this->width < other.x + other.width) ? this->x + this->width : other.x + other.width;
    int bottom = (this->y + this->height < other.y + other.height) ? this->y + this->height : other.y + other.height;

    int w = right - left;
    int h = bottom - top;

    if (w < 0) w = 0;
    if (h < 0) h = 0;

    return Rectangle(left, top, w, h);
}

Rectangle Rectangle::operator|(const Rectangle& other) const {
    int left = (this->x < other.x) ? this->x : other.x;
    int top = (this->y < other.y) ? this->y : other.y;
    int right = (this->x + this->width > other.x + other.width) ? this->x + this->width : other.x + other.width;
    int bottom = (this->y + this->height > other.y + other.height) ? this->y + this->height : other.y + other.height;

    int w = right - left;
    int h = bottom - top;

    return Rectangle(left, top, w, h);
}