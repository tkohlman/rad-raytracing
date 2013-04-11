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
        m_width(width),
        m_height(height)
    {
        m_pixels = new std::vector<Color>(width * height, Color::BLACK);
    };

    virtual ~Image()
    {
        delete m_pixels;
    }

    int width() const { return m_width; };
    int height() const { return m_height; };

    Color *get_pixel(int row, int column) const
    {
        int index = row * m_width + column;
        return &m_pixels->at(index);
    }

    void set_pixel(int row, int column, const Color &color) const
    {
        int index = row * m_width + column;
        m_pixels->at(index) = color;
    }

private:

    int m_width;
    int m_height;

    std::vector<Color> *m_pixels;
};

}   // namespace RadRt

#endif // IMAGE_H_INCLUDED
