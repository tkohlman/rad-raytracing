/*
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 */

#ifndef IMAGE_H_INCLUDED
#define IMAGE_H_INCLUDED

#include "color.h"
#include <vector>

namespace RadRt
{

class Image
{
public:

    Image(int width, int height):
        width(width),
        height(height)
    {
        pixels = new std::vector<Color>(width * height, Color::BLACK);
    };

    virtual ~Image()
    {
        delete pixels;
    }

    int getWidth() const { return width; };
    int getHeight() const { return height; };

    Color *getPixel(int row, int column) const
    {
        int index = row * width + column;
        return &pixels->at(index);
    }

    void setPixel(int row, int column, const Color &color) const
    {
        int index = row * width + column;
        pixels->at(index) = color;
    }

private:

    int width;
    int height;

    std::vector<Color> *pixels;
};

}   // namespace RadRt

#endif // IMAGE_H_INCLUDED
