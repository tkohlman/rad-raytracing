/*
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 */

#include "canvas.h"
#include "color.h"
#include "image.h"

#include <gdkmm/general.h>

namespace RadRt
{

const bool Canvas::HAS_ALPHA = true;
const int Canvas::BITS_PER_SAMPLE = 8;
const int Canvas::RED_CHANNEL = 0;
const int Canvas::GREEN_CHANNEL = 1;
const int Canvas::BLUE_CHANNEL = 2;
const int Canvas::ALPHA_CHANNEL = 3;

Canvas::Canvas():
    m_width(0),
    m_height(0)
{
}

Canvas::~Canvas()
{
}

void Canvas::draw_image(Image *image)
{
    m_width = image->width();
    m_height = image->height();

    m_canvas = Gdk::Pixbuf::create(Gdk::COLORSPACE_RGB,
                                 HAS_ALPHA,
                                 BITS_PER_SAMPLE,
                                 m_width,
                                 m_height);

    // Iterate over the pixels and render them.
    for (int row = 0; row < m_height; ++row)
    {
        for (int column = 0; column < m_width; ++column)
        {
            set_pixel(m_height - row - 1, column, *image->get_pixel(row, column));
        }
    }

    queue_draw();
}

void Canvas::clear()
{
    Gtk::Allocation allocation = get_allocation();
    m_width  = allocation.get_width();
    m_height = allocation.get_height();

    m_canvas = Gdk::Pixbuf::create(Gdk::COLORSPACE_RGB, HAS_ALPHA, BITS_PER_SAMPLE,
                            m_width, m_height);
    for (int column = 0; column < m_width; ++column)
    {
        for (int row = 0; row < m_height; ++row)
        {
            ((column & 0x40) && (row & 0x40)) ||
            (!(column & 0x40) && !(row & 0x40)) ?
            set_pixel(row, column, RadRt::Color::BLACK) :
            set_pixel(row, column, RadRt::Color::WHITE);
        }
    }

    queue_draw();
}


void Canvas::set_pixel(int row, int column, const Color &color)
{
    if (m_canvas == false)
    {
        return;
    }

    guchar *pixels, *offset;

    const int n_channels = m_canvas->get_n_channels();
    const int rowstride = m_canvas->get_rowstride();

    unsigned char red, green, blue, alpha;
    red = green = blue = alpha = 0xFF;

    if (color.red() < 1)
    {
        red *= color.red();
    }

    if (color.green() < 1)
    {
        green *= color.green();
    }

    if (color.blue() < 1)
    {
        blue *= color.blue();
    }

    g_assert (m_canvas->get_colorspace() == Gdk::COLORSPACE_RGB);
    g_assert (m_canvas->get_bits_per_sample() == BITS_PER_SAMPLE);
    g_assert (m_canvas->get_has_alpha());
    g_assert (n_channels == 4);

    g_assert (column >= 0 && column < m_width);
    g_assert (row >= 0 && row < m_height);

    pixels = m_canvas->get_pixels();

    offset = pixels + row * rowstride + column * n_channels;
    offset[RED_CHANNEL]   = red;
    offset[GREEN_CHANNEL] = green;
    offset[BLUE_CHANNEL]  = blue;
    offset[ALPHA_CHANNEL] = alpha;
}

bool Canvas::on_draw(const Cairo::RefPtr<Cairo::Context>& context)
{
    if (m_canvas == false)
    {
        return false;
    }

    Gtk::Allocation allocation = get_allocation();
    const int allocated_width  = allocation.get_width();
    const int allocated_height = allocation.get_height();

    // Attempt to draw the canvas in the center of the drawing area. If the
    // canvas is larger than the drawing area, draw the center of the canvas.
    Gdk::Cairo::set_source_pixbuf(context, m_canvas, (allocated_width - m_width)/2,
                                  (allocated_height - m_height)/2);
    context->paint();

    return true;
}

}  // namespace RadRt
