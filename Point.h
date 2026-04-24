//
// Created by Ana on 4/24/2026.
//

#ifndef IMAGEPROCESSINGLIBRARY_POINT_H
#define IMAGEPROCESSINGLIBRARY_POINT_H
#include <ratio>


class Point {
    int x;
    int y;
public:
    Point();
    Point(int x, int y);
    void SetX(int x);
    void SetY(int y);
    unsigned int GetX() const;
    unsigned int GetY() const;
};


#endif //IMAGEPROCESSINGLIBRARY_POINT_H