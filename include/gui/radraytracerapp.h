/*
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 */

#ifndef RADRAYTRACERAPP_H_INCLUDED
#define RADRAYTRACERAPP_H_INCLUDED

#include "canvas.h"
#include "image.h"

#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/menu.h>
#include <gtkmm/menubar.h>

namespace RadRt
{

class Scene;

class RadRaytracerApp : public Gtk::Window
{
public:

    RadRaytracerApp();
    virtual ~RadRaytracerApp();

    void setCanvas(Canvas *canvas);

    void save_scene(const char *filename, const RadRt::Scene &scene);
    void open_scene(const char *filename, RadRt::Scene *scene);

    void run_raytracer(RadRt::Scene * scene);

private:

    void init();

    Gtk::Box box;

    Gtk::MenuBar main_menu_bar;
    Gtk::Menu main_menu;

    Gtk::Menu file_submenu;
    Gtk::Menu help_submenu;

    Gtk::MenuItem file_menu;
    Gtk::MenuItem edit_menu;
    Gtk::MenuItem help_menu;

    Gtk::MenuItem quit_menu;
    Gtk::MenuItem about_menu;

    Canvas *canvas;

    RadRt::Image *image;

};

}   // namespace RadRt

#endif // RADRAYTRACERAPP_H_INCLUDED
