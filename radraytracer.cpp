///
/// @file cp7.cpp
///
/// @author	Thomas Kohlman
/// @date 21 January 2012
///
/// @description
/// 	Checkpoint 7 - Tone Reproduction
///
///
///

#include <GL/glut.h>
#include "Raytracer.h"
#include "ToneReproducer.h"
using namespace Raytracer_n;
#include "scene.h"

#include <vector>
#include <unistd.h>
#include <fstream>
#include <iostream>
using namespace std;

const int WINDOW_POS_X = 100;
const int WINDOW_POS_Y = 100;

#define LMAX    1000
#define LDMAX   100

int aflag = 0;      /* specify tone reproduction algorithm */
int bflag = 0;      /* specify the number of bounces */
int fflag = 0;      /* specify output file format */
int hflag = 0;      /* display the usage message */
int lflag = 0;      /* specify lmax value for tone reproduction */
int oflag = 0;      /* specify output file */
int sflag = 0;      /* scecify a sence.obj file to render */

int lmax = 0;
int algo = 0;
int depth = 1;

void render(Scene *scene, PixelBuffer2D *pixels)
{
    // Iterate over the pixels and render them.
    for (int j = 0; j < scene->getHeight(); ++j)
    {
        for (int i = 0; i < scene->getWidth(); ++i)
        {
            float r_comp = pixels->at(j)->at(i).getR();
            float g_comp = pixels->at(j)->at(i).getG();
            float b_comp = pixels->at(j)->at(i).getB();

            // Set the color
            glColor3f(r_comp, g_comp, b_comp);

            // Draw the point
            glBegin(GL_POINTS);
	        glVertex2i(i, j);
            glEnd();
        }
    }
}

void save_scene(const char *filename, const Scene &scene)
{
    filebuf fb;
    fb.open (filename, ios::out);
    ostream os(&fb);
    Json::Value root = scene.serialize();
    os << root << endl;
    fb.close();
}

void open_scene(const char *filename, Scene *scene)
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

PixelBuffer2D *pixels = NULL;
Scene *scene = NULL;

void run_raytracer()
{
    //scene = make_scene();

    // Create the raytracer
    Raytracer raytracer;
    raytracer.setMaxDepth(depth);

    pixels = raytracer.TraceScene(scene);

    if (aflag && lflag)
    {
        // Tone Reproduction Steps
        ToneReproducer tr(lmax, LDMAX, scene->getHeight(), scene->getWidth());
        tr.Run(pixels, algo);
    }
}



void display( void )
{
    render(scene, pixels);

    // Display new screen
    glutSwapBuffers();
}

void usage()
{
    cout << "Usage: raytrace "      << endl;
    cout << "\t-a <0 (Ward) | 1 (Reinhard)>" << endl;
    cout << "\t-f <format: PNG>"    << endl;
    cout << "\t-l <lmax>"           << endl;
    cout << "\t-o <output file>"    << endl;
    cout << "\t-s <scene.obj>"      << endl;

    exit(1);
}

int main( int argc, char** argv )
{
    int op;
    opterr = 0;
	while ((op = getopt(argc, argv, "a:b:f:hl:o:s:")) != -1)
    {
		switch (op) {

        case 'a':
            ++aflag;
            algo = strtof(optarg, NULL);
            if (algo == 0)
                algo = WARDS;
            else
                algo = REINHARDS;
            break;

        case 'b':
            ++bflag;
            depth = atoi(optarg);
            break;

		case 'f':
			++fflag;
			cout << "Warning: f flag not yet implemented" << endl;
			break;

        case 'h':
            usage();
            /* NOT REACHED */

		case 'l':
			++lflag;
			lmax = atoi(optarg);
			break;

		case 'o':
			++oflag;
			cout << "Warning: o flag not yet implemented" << endl;
			break;

		case 's':
			++sflag;
			cout << "Warning: s flag not yet implemented" << endl;
			break;

		default:
			usage();
			/* NOTREACHED */
		}
    }
    //scene = make_scene();
    //save_scene("scene.txt", *scene);
    scene = new Scene();
    open_scene("whitted.json", scene);

    run_raytracer();

    // OpenGL Dependency:

   	glutInit( &argc, argv );
   	glutInitDisplayMode( GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE );
   	glutInitWindowSize(scene->getWidth(), scene->getHeight());
   	glutInitWindowPosition(WINDOW_POS_X, WINDOW_POS_Y);
   	glutCreateWindow("Rad::Raytracer");

	glLoadIdentity();
	gluOrtho2D(0, scene->getWidth(), 0, scene->getHeight());

   	// Callback functions
   	glutDisplayFunc( display );

   	glutMainLoop( );

   	return 0;

}



