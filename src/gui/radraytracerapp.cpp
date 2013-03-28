/*
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 */

#include "radraytracerapp.h"

#include "raytracer.h"
#include "tonereproducer.h"
#include "scene.h"

#include <fstream>

#define LMAX    1000
#define LDMAX   100


int lmax = 0;
int algo = 0;
int depth = 3;

int aflag = 0;      /* specify tone reproduction algorithm */
int lflag = 0;      /* specify lmax value for tone reproduction */

namespace RadRt
{

RadRaytracerApp::RadRaytracerApp() : box(Gtk::ORIENTATION_VERTICAL),
                                     canvas(nullptr),
                                     image(nullptr)
{
    init();
}

RadRaytracerApp::~RadRaytracerApp()
{
    if (canvas != nullptr)
    {
        delete canvas;
    }
}

void RadRaytracerApp::init()
{
    file_menu.set_label("File");
    edit_menu.set_label("Edit");
    help_menu.set_label("Help");

    quit_menu.set_label("Quit");
    about_menu.set_label("About");

    help_submenu.append(about_menu);
    help_menu.set_submenu(help_submenu);

    file_submenu.append(quit_menu);
    file_menu.set_submenu(file_submenu);

    main_menu_bar.append( file_menu );
    main_menu_bar.append( edit_menu );
    main_menu_bar.append( help_menu );

    //about_menu.signal_activate().connect(sigc::ptr_fun(&on_about_activated));
    //quit_menu.signal_activate().connect(sigc::ptr_fun(&Gtk::Main::quit));

    Scene *scene = new RadRt::Scene();
    open_scene("/home/thomas/Documents/git/rad-raytracing/scenes/whitted.json", scene);

    int width = scene->getWidth();
    int height = scene->getHeight();
    RadRt::Canvas *canvas = new RadRt::Canvas(width, height);
/*
    for (int column = 0; column < width; ++column)
    {
        for (int row = 0; row < height; ++row)
        {
            ((column & 0x40) && (row & 0x40)) ||
            (!(column & 0x40) && !(row & 0x40)) ?
            canvas->setPixel(row, column, RadRt::Color::BLACK) :
            canvas->setPixel(row, column, RadRt::Color::WHITE);
        }
    }
*/
    run_raytracer(scene);

    // Iterate over the pixels and render them.
    for (int row = 0; row < scene->getHeight(); ++row)
    {
        for (int column = 0; column < scene->getWidth(); ++column)
        {
            canvas->setPixel(height - row - 1, column, *image->getPixel(row, column));
        }
    }

    delete image;
    delete scene;

    box.pack_start(main_menu_bar, Gtk::PACK_SHRINK);
    box.pack_start(*canvas);
    add(box);

    set_title("Rad-Raytracing - version 1.0");
    set_default_size(width, height);

    show_all_children();
}

void RadRaytracerApp::save_scene(const char *filename, const RadRt::Scene &scene)
{
    std::filebuf file_buffer;
    file_buffer.open(filename, std::ios::out);
    std::ostream os(&file_buffer);
    Json::Value root = scene.serialize();
    os << root << std::endl;
    file_buffer.close();
}

void RadRaytracerApp::open_scene(const char *filename, RadRt::Scene *scene)
{
    Json::Value root;   // will contains the root value after parsing.
    Json::Reader reader;
    std::string file_contents;
    std::ifstream in(filename, std::ios::in | std::ios::binary);
    if (in)
    {
        in.seekg(0, std::ios::end);
        file_contents.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&file_contents[0], file_contents.size());
        in.close();
    }

    bool parsingSuccessful = reader.parse(file_contents, root);
    if (!parsingSuccessful)
    {
        // report to the user the failure and their locations in the document.
        std::cerr  << "Failed to parse configuration\n"
                   << reader.getFormattedErrorMessages();
        return;
    }

    scene->deserialize(root);
}

void RadRaytracerApp::run_raytracer(RadRt::Scene * scene)
{
    // Create the raytracer
    RadRt::Raytracer raytracer;
    raytracer.setMaxDepth(depth);

    image = raytracer.traceScene(scene);

    if (aflag && lflag)
    {
        // Tone Reproduction Steps
        RadRt::ToneReproducer tr(lmax, LDMAX, scene->getHeight(), scene->getWidth());
        tr.run(image, algo);
    }
}

}   // namespace RadRt
