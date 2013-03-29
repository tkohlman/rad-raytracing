/*
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 */

#ifndef RADRAYTRACERAPP_H_INCLUDED
#define RADRAYTRACERAPP_H_INCLUDED

#include "canvas.h"
#include "image.h"

#include <gtkmm/button.h>
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

    void save_scene(const char *filename);
    void open_scene(const char *filename);

    void run_raytracer();

protected:

    void on_open_scene_clicked();
    void on_clear_clicked();
    void on_quit_clicked();

private:

    void init();

    void render_scene();

    Gtk::Box box;

    Gtk::Button btnClear;

    Gtk::MenuBar main_menu_bar;
    Gtk::Menu main_menu;

    Gtk::Menu file_submenu;
    Gtk::Menu help_submenu;

    Gtk::MenuItem file_menu;
    Gtk::MenuItem edit_menu;
    Gtk::MenuItem help_menu;

    Gtk::MenuItem open_scene_menu;

    Gtk::MenuItem quit_menu;
    Gtk::MenuItem about_menu;

    Canvas *canvas;

    RadRt::Image *image;
    RadRt::Scene *scene;

};

}   // namespace RadRt

#endif // RADRAYTRACERAPP_H_INCLUDED
