/*
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 */

#ifndef CANVAS_H_INCLUDED
#define CANVAS_H_INCLUDED

#include <gtkmm/drawingarea.h>
#include <cairomm/context.h>

namespace RadRt
{

class Color;
class Image;

class Canvas : public Gtk::DrawingArea
{
public:

    static const bool HAS_ALPHA;
    static const int BITS_PER_SAMPLE;
    static const int RED_CHANNEL;
    static const int GREEN_CHANNEL;
    static const int BLUE_CHANNEL;
    static const int ALPHA_CHANNEL;

    Canvas();
    virtual ~Canvas();

    void draw_image(Image *image);
    void clear();

protected:

    virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);

    void set_pixel(int row, int column, const Color  &color);

private:

    Glib::RefPtr<Gdk::Pixbuf> m_canvas;

    int m_width;
    int m_height;
};

}   // namespace RadRt

#endif // CANVAS_H_INCLUDED
