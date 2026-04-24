//
// Created by Ana on 4/24/2026.
//

#ifndef IMAGEPROCESSINGLIBRARY_SIZE_H
#define IMAGEPROCESSINGLIBRARY_SIZE_H


class Size {
    unsigned int witdth;
    unsigned int height;

    public:
    Size();
    Size(unsigned int w, unsigned int h);
    void SetWidth(unsigned int w);
    void SetHeight(unsigned int h);
    unsigned int GetWidth() const;
    unsigned int GetHeight() const;
    bool operator==(const Size& other) const;
    bool operator!=(const Size& other) const;
    bool operator>(const Size& other) const;
    bool operator<(const Size& other) const;
    bool operator>=(const Size& other) const;
    bool operator<=(const Size& other) const;


};


#endif //IMAGEPROCESSINGLIBRARY_SIZE_H