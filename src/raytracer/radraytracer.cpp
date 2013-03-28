/*
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 */

#include "radraytracerapp.h"

int main( int argc, char** argv )
{
    Glib::RefPtr<Gtk::Application> app =
    Gtk::Application::create(argc, argv, "com.radraytracing",
    Gio::APPLICATION_NON_UNIQUE |
    Gio::APPLICATION_HANDLES_OPEN);

    RadRt::RadRaytracerApp raytracer;

    return app->run(raytracer);
}

