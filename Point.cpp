//
// Created by Ana on 4/24/2026.
//

#include "Point.h"

Point::Point() {
    this->x = 0;
    this->y = 0;
}

Point::Point(int x, int y) {
    this->x = x;
    this->y = y;
}

void Point::SetX(int x) {
    this->x=x;
}

void Point::SetY(int y) {
    this->y=y;
}

unsigned int Point::GetX() const {
    return x;
}

unsigned int Point::GetY() const {
    return y;
}
