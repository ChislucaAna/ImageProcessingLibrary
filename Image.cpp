//
// Created by Ana on 4/24/2026.
//

#include "Image.h"
#include <stdexcept>
#include <algorithm>

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

void Image::release() {
    if (m_data != nullptr) {
        for (unsigned int i = 0; i < m_height; i++) {
            delete[] m_data[i];
        }
        delete[] m_data;
        m_data = nullptr;
        m_width = 0;
        m_height = 0;
    }
}

Image::~Image() {
    release();
}

unsigned int Image::width() const {
    return this->m_width;
}

unsigned int Image::height() const {
    return this->m_height;
}
Size Image::size() const {
    return Size(this->m_width, this->m_height);
}

bool Image::isEmpty() const {
    if (this->m_data != nullptr)
        return false;
    if (this->m_width != 0 || this->m_height != 0)
        return false;
    return true;
}

bool Image::load(std::string imagePath) {
    std::ifstream file(imagePath);
    if (!file.is_open()) {
        return false;
    }
    file >> *this;
    file.close();
    return true;
}

bool Image::save(std::string imagePath) const {
    std::ofstream file(imagePath);
    if (!file.is_open()) {
        return false;
    }
    file << *this;
    file.close();
    return true;
}

Image Image::zeros(unsigned int width, unsigned int height) {
    Image img(width, height);
    return img;
}

Image Image::ones(unsigned int width, unsigned int height) {
    Image img(width, height);
    if (img.m_data != nullptr) {
        for (unsigned int i = 0; i < height; i++) {
            for (unsigned int j = 0; j < width; j++) {
                img.m_data[i][j] = 1;
            }
        }
    }
    return img;
}

unsigned char& Image::at(unsigned int x, unsigned int y) const{
    return this->m_data[y][x];
}

unsigned char& Image::at(Point pt) {
    return this->m_data[pt.GetY()][pt.GetX()];
}

unsigned char* Image::row(int y) {
    if (y < 0 || y >= (int)this->m_height) {
        return nullptr;
    }
    return this->m_data[y];
}

Image Image::operator+(const Image &i) {
    if (this->m_width != i.m_width || this->m_height != i.m_height) {
        throw std::runtime_error("Images must have the same dimensions for addition");
    }

    Image result(this->m_width, this->m_height);
    for (unsigned int row = 0; row < this->m_height; row++) {
        for (unsigned int col = 0; col < this->m_width; col++) {
            int sum = (int)this->m_data[row][col] + (int)i.m_data[row][col];
            result.m_data[row][col] = (unsigned char)std::min(sum, 255);
        }
    }
    return result;
}

Image Image::operator-(const Image &i) {
    if (this->m_width != i.m_width || this->m_height != i.m_height) {
        throw std::runtime_error("Images must have the same dimensions for subtraction");
    }

    Image result(this->m_width, this->m_height);
    for (unsigned int row = 0; row < this->m_height; row++) {
        for (unsigned int col = 0; col < this->m_width; col++) {
            int diff = (int)this->m_data[row][col] - (int)i.m_data[row][col];
            result.m_data[row][col] = (unsigned char)std::max(diff, 0);
        }
    }
    return result;
}

Image Image::operator*(double s) {
    Image result(this->m_width, this->m_height);
    for (unsigned int row = 0; row < this->m_height; row++) {
        for (unsigned int col = 0; col < this->m_width; col++) {
            double product = (double)this->m_data[row][col] * s;
            result.m_data[row][col] = (unsigned char)std::min(std::max(product, 0.0), 255.0);
        }
    }
    return result;
}

bool Image::getROI(Image &roiImg, Rectangle roiRect) {
    int x = roiRect.getX();
    int y = roiRect.getY();
    unsigned int width = roiRect.getWidth();
    unsigned int height = roiRect.getHeight();

    return getROI(roiImg, x, y, width, height);
}

bool Image::getROI(Image &roiImg, unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
    // Check if ROI is within image bounds
    if (x + width > this->m_width || y + height > this->m_height) {
        return false;
    }

    // Resize roiImg to the ROI dimensions
    roiImg.m_width = width;
    roiImg.m_height = height;

    // Free old data if it exists
    if (roiImg.m_data != nullptr) {
        for (unsigned int i = 0; i < roiImg.m_height; i++) {
            delete[] roiImg.m_data[i];
        }
        delete[] roiImg.m_data;
    }

    // Allocate memory for ROI image
    roiImg.m_data = new unsigned char*[height];
    for (unsigned int i = 0; i < height; i++) {
        roiImg.m_data[i] = new unsigned char[width];
    }

    // Copy pixel data from source to ROI
    for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < width; j++) {
            roiImg.m_data[i][j] = this->m_data[y + i][x + j];
        }
    }

    return true;
}

std::ostream& operator<<(std::ostream& os, const Image& dt) {
    // Write PGM header
    os << "P2\n";
    os << "# Image file\n";
    os << dt.m_width << " " << dt.m_height << "\n";
    os << "255\n";

    // Write pixel data
    if (dt.m_data != nullptr) {
        for (unsigned int i = 0; i < dt.m_height; i++) {
            for (unsigned int j = 0; j < dt.m_width; j++) {
                os << (int)dt.m_data[i][j];
                if (j < dt.m_width - 1) os << " ";
            }
            os << "\n";
        }
    }

    return os;
}

std::istream& operator>>(std::istream& is, Image& dt) {
    std::string magic;
    is >> magic;

    // Consume the rest of the magic-number line, then skip comment lines
    std::string line;
    std::getline(is, line);
    while (is.peek() == '#') {
        std::getline(is, line);
    }

    unsigned int width, height, maxVal;
    is >> width >> height >> maxVal;

    // Free old memory if it exists
    if (dt.m_data != nullptr) {
        for (unsigned int i = 0; i < dt.m_height; i++) {
            delete[] dt.m_data[i];
        }
        delete[] dt.m_data;
    }

    // Set new dimensions
    dt.m_width = width;
    dt.m_height = height;

    // Allocate memory for the new image
    dt.m_data = new unsigned char*[height];
    for (unsigned int i = 0; i < height; i++) {
        dt.m_data[i] = new unsigned char[width];
    }

    // Read pixel data
    for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < width; j++) {
            int pixel;
            is >> pixel;
            dt.m_data[i][j] = (unsigned char)pixel;
        }
    }

    return is;
}


