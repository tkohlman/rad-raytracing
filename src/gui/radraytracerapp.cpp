/*
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 */

#include "radraytracerapp.h"

#include "raytracer.h"
#include "tonereproducer.h"
#include "scene.h"

#include <fstream>
#include <gtkmm/filechooserdialog.h>
#include <gtkmm/stock.h>

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
                                     image(nullptr),
                                     scene(nullptr)
{
    canvas = new Canvas();
    init();
}

RadRaytracerApp::~RadRaytracerApp()
{
    if (canvas != nullptr)
        delete canvas;

    if (scene != nullptr)
        delete scene;

    if (image != nullptr)
        delete image;
}

void RadRaytracerApp::init()
{

    edit_menu.set_label("Edit");
    help_menu.set_label("Help");

    about_menu.set_label("About");

    file_menu.set_label("File");

    open_scene_menu.set_label("Open Scene...");
    open_scene_menu.signal_activate().connect(sigc::mem_fun(*this,
              &RadRaytracerApp::on_open_scene_clicked));

    quit_menu.set_label("Quit");
    quit_menu.signal_activate().connect(sigc::mem_fun(*this,
              &RadRaytracerApp::on_quit_clicked));
    file_submenu.append(open_scene_menu);
    file_submenu.append(quit_menu);
    file_menu.set_submenu(file_submenu);

    help_submenu.append(about_menu);
    help_menu.set_submenu(help_submenu);

    main_menu_bar.append( file_menu );
    main_menu_bar.append( edit_menu );
    main_menu_bar.append( help_menu );

    btnClear.set_label("Clear Canvas");
    btnClear.signal_clicked().connect(sigc::mem_fun(*this,
              &RadRaytracerApp::on_clear_clicked));

    //about_menu.signal_activate().connect(sigc::ptr_fun(&on_about_activated));
    //quit_menu.signal_activate().connect(sigc::ptr_fun(&Gtk::Main::quit));

    std::string filename =
        "/home/thomas/Documents/git/rad-raytracing/scenes/whitted.json";
    open_scene(filename.c_str());

    render_scene();

    lblSceneName.set_text(filename);

    box.pack_start(main_menu_bar, Gtk::PACK_SHRINK);
    box.pack_start(lblSceneName, Gtk::PACK_SHRINK);
    box.pack_start(btnClear, Gtk::PACK_SHRINK);
    box.pack_start(*canvas);
    add(box);

    set_title("Rad-Raytracing - version 1.0");
    set_default_size(1200, 700);

    show_all_children();
}

void RadRaytracerApp::on_clear_clicked()
{
    canvas->clear();
}

void RadRaytracerApp::on_quit_clicked()
{
    hide();
}

void RadRaytracerApp::render_scene()
{
    if (scene == nullptr)
        return;

    run_raytracer();
    canvas->drawImage(image);
}

void RadRaytracerApp::save_scene(const char *filename)
{
    std::filebuf file_buffer;
    file_buffer.open(filename, std::ios::out);
    std::ostream os(&file_buffer);
    Json::Value root = scene->serialize();
    os << root << std::endl;
    file_buffer.close();
}

void RadRaytracerApp::on_open_scene_clicked()
{
    Gtk::FileChooserDialog dialog("Please choose a scene file",
                                  Gtk::FILE_CHOOSER_ACTION_OPEN);
    dialog.set_transient_for(*this);

    //Add response buttons the the dialog:
    dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
    dialog.add_button(Gtk::Stock::OPEN, Gtk::RESPONSE_OK);

    //Add filters, so that only certain file types can be selected:
    Glib::RefPtr<Gtk::FileFilter> filter_json = Gtk::FileFilter::create();
    filter_json->set_name("JSON Files");
    filter_json->add_pattern("*.json");
    dialog.add_filter(filter_json);

    int result = dialog.run();

    switch(result)
    {
        case(Gtk::RESPONSE_OK):
        {
            std::string filename = dialog.get_filename();
            open_scene(filename.c_str());
            lblSceneName.set_text(filename);
            render_scene();
            break;
        }
        default:
            break;
    }
}

void RadRaytracerApp::open_scene(const char *filename)
{
    Json::Value root;
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
        std::cerr  << "Failed to parse configuration\n"
                   << reader.getFormattedErrorMessages();
        return;
    }

    if (scene != nullptr)
    {
        delete scene;
    }
    scene = new Scene();
    scene->deserialize(root);
}

void RadRaytracerApp::run_raytracer()
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
