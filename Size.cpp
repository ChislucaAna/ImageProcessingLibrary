//
// Created by Ana on 4/24/2026.
//

#include "Size.h"

Size::Size() {
    this->witdth=0;
    this->height=0;
}

Size::Size(unsigned int w, unsigned int h) {
    this->witdth=w;
    this->height=h;
}

void Size::SetWidth(unsigned int w) {
    this->witdth=w;
}

void Size::SetHeight(unsigned int h) {
    this->height=h;
}

unsigned int Size::GetWidth() const {
    return this->witdth;
}

unsigned int Size::GetHeight() const{
    return this->height;
}


bool Size::operator==(const Size& other) const {
    return this->witdth*this->height==other.witdth*other.height;
}

bool Size::operator!=(const Size& other) const {
    return this->witdth*this->height!=other.witdth*other.height;
}

bool Size::operator<(const Size& other) const {
    return this->witdth*this->height<other.witdth*other.height;
}

bool Size::operator>(const Size& other) const {
    return this->witdth*this->height>other.witdth*other.height;
}

bool Size::operator<=(const Size& other) const {
    return this->witdth*this->height<=other.witdth*other.height;
}

bool Size::operator>=(const Size& other) const {
    return this->witdth*this->height>=other.witdth*other.height;
}