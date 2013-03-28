/*
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 */

#include "canvas.h"
#include "color.h"

#include <gdkmm/general.h>

namespace RadRt
{

const bool Canvas::HAS_ALPHA = true;
const int Canvas::BITS_PER_SAMPLE = 8;
const int Canvas::RED_CHANNEL = 0;
const int Canvas::GREEN_CHANNEL = 1;
const int Canvas::BLUE_CHANNEL = 2;
const int Canvas::ALPHA_CHANNEL = 3;

Canvas::Canvas(int width, int height): width(width), height(height)
{
    image = Gdk::Pixbuf::create(Gdk::COLORSPACE_RGB, HAS_ALPHA, BITS_PER_SAMPLE,
                                width, height);
}

Canvas::~Canvas()
{
}

void Canvas::setPixel(int row, int column, const Color &color)
{
    guchar *pixels, *offset;

    const int n_channels = image->get_n_channels();
    const int rowstride = image->get_rowstride();

    unsigned char red, green, blue, alpha;
    red = green = blue = alpha = 0xFF;

    if (color.getR() < 1)
    {
        red *= color.getR();
    }

    if (color.getG() < 1)
    {
        green *= color.getG();
    }

    if (color.getB() < 1)
    {
        blue *= color.getB();
    }

    g_assert (image->get_colorspace() == Gdk::COLORSPACE_RGB);
    g_assert (image->get_bits_per_sample() == BITS_PER_SAMPLE);
    g_assert (image->get_has_alpha());
    g_assert (n_channels == 4);

    g_assert (column >= 0 && column < width);
    g_assert (row >= 0 && row < height);

    pixels = image->get_pixels();

    offset = pixels + row * rowstride + column * n_channels;
    offset[RED_CHANNEL]   = red;
    offset[GREEN_CHANNEL] = green;
    offset[BLUE_CHANNEL]  = blue;
    offset[ALPHA_CHANNEL] = alpha;
}

bool Canvas::on_draw(const Cairo::RefPtr<Cairo::Context>& context)
{
    if (image == false)
    {
        return false;
    }

    Gtk::Allocation allocation = get_allocation();
    const int allocated_width  = allocation.get_width();
    const int allocated_height = allocation.get_height();

    // Attempt to draw the image in the center of the drawing area. If the
    // image is larger than the drawing area, draw the center of the image.
    Gdk::Cairo::set_source_pixbuf(context, image, (allocated_width - width)/2,
                                  (allocated_height - height)/2);
    context->paint();

    return true;
}

}  // namespace RadRt
