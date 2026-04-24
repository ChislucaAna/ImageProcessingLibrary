//
// Created by Ana on 4/24/2026.
//

#include "Image.h"

Image::Image() {
    this->m_width=0;
    this->m_height=0;
    this->m_data=nullptr;
}

Image::Image(unsigned int w, unsigned int h) {
    this->m_width = w;
    this->m_height = h;

    this->m_data = new unsigned char*[h];
    for (unsigned int i = 0; i < h; i++) {
        this->m_data[i] = new unsigned char[w](); //sets all pixels to zero
    }
}

Image::Image(const Image &other) {
    this->m_width = other.m_width;
    this->m_height = other.m_height;

    if (other.m_data != nullptr) {
        this->m_data = new unsigned char*[m_height];

        //you want a deep copy so go row by row,
        //cell by cell for assginment
        for (unsigned int i = 0; i < m_height; i++) {
            this->m_data[i] = new unsigned char[m_width];
            for (unsigned int j = 0; j < m_width; j++) {
                this->m_data[i][j] = other.m_data[i][j];
            }
        }
    } else {
        this->m_data = nullptr;
    }
}

Image& Image::operator=(const Image &other) {
    //Prevent self-assignment
    if (this != &other) {
        // Free old memory properly
        if (this->m_data != nullptr) {
            //must delete the row first
            for (unsigned int i = 0; i < m_height; i++) {
                delete[] this->m_data[i];
            }
            //then delete the structure
            delete[] this->m_data;
        }

        this->m_width = other.m_width;
        this->m_height = other.m_height;

        //the same logic as in copy constructor->you want a deep copy
        if (other.m_data != nullptr) {
            this->m_data = new unsigned char*[m_height];

            for (unsigned int i = 0; i < m_height; i++) {
                this->m_data[i] = new unsigned char[m_width];
                for (unsigned int j = 0; j < m_width; j++) {
                    this->m_data[i][j] = other.m_data[i][j];
                }
            }
        }
        else {
            this->m_data = nullptr;
        }
    }
    return *this;
}

/*
Think of it like a parking garage:
  - You allocated spots for 10 cars (the array of pointers)
  - You allocated a garage for each car (each row)
  - You must empty each garage first, then remove the spots
  */
Image::~Image() {
    if (this->m_data != nullptr) {
        //go row by row to delete the constents of the row
        for (unsigned int i = 0; i < m_height; i++) {
            delete[] this->m_data[i];
        }
        //then detele the big structure
        delete[] this->m_data;
    }
}

