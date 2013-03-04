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
#include "Vector.h"
#include "Point.h"
#include "Rectangle.h"
#include "cylinder.h"
#include "Sphere.h"
#include "Light.h"
#include "Raytracer.h"
#include "PhongShader.h"
#include "ToneReproducer.h"
#include "Scene.h"

using namespace Raytracer_n;
#include "scene.h"
#include "checkedshader.h"

#include <vector>
#include <unistd.h>
#include <fstream>
#include <iostream>
using namespace std;

#define WINDOW_TITLE "Ray Tracer - Checkpoint 7"

#define WINDOW_HEIGHT 275
#define WINDOW_WIDTH  350

#define WINDOW_POS_X  100
#define WINDOW_POS_Y  100

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
            float r_comp = pixels->at(j)->at(i).R();
            float g_comp = pixels->at(j)->at(i).G();
            float b_comp = pixels->at(j)->at(i).B();

            // Set the color
            glColor3f(r_comp, g_comp, b_comp);

            // Draw the point
            glBegin(GL_POINTS);
	        glVertex2i(i, j);
            glEnd();
        }
    }
}

Scene *make_scene()
{
    Scene *scene = new Scene();
    scene->setWidth(WINDOW_WIDTH);
    scene->setHeight(WINDOW_HEIGHT);
    scene->setBackground(BACKGROUND_COLOR);

    Camera camera;
    camera.setLocation(CAMERA_POSITION);

    scene->setCamera(camera);

// Cylinder Constants
#define CYL_RADIUS  1

#define CYL_POS_1_X -10
#define CYL_POS_1_Y -12
#define CYL_POS_1_Z -15

#define CYL_POS_2_X -4
#define CYL_POS_2_Y  0
#define CYL_POS_2_Z -5

#define CYL_COL_R 0.1
#define CYL_COL_G 0.2
#define CYL_COL_B 0.3

    Color cyl_color(CYL_COL_R, CYL_COL_G, CYL_COL_B);
    Point cyl_cp1(CYL_POS_1_X, CYL_POS_1_Y, CYL_POS_1_Z);
    Point cyl_cp2(CYL_POS_2_X, CYL_POS_2_Y, CYL_POS_2_Z);
    Cylinder *cylinder = new Cylinder(cyl_cp1, cyl_cp2, CYL_RADIUS,
                                SPHERE_2_AMBIENT,
                                SPHERE_2_DIFFUSE,
                                SPHERE_2_SPECULAR,
                                SPHERE_2_KA,
                                SPHERE_2_KD,
                                SPHERE_2_KS,
                                SPHERE_2_EXPONENT,
                                SPHERE_2_KR,
                                SPHERE_2_KT,
                                SPHERE_2_IR);
    scene->addShape(cylinder);

    // Create the rectangle (floor)
    Rectangle *r = new Rectangle(FLOOR_A, FLOOR_B, FLOOR_C, FLOOR_D,
                                   FLOOR_AMBIENT,
                                   FLOOR_DIFFUSE,
                                   FLOOR_SPECULAR,
                                   FLOOR_KA,
                                   FLOOR_KD,
                                   FLOOR_KS,
                                   FLOOR_EXPONENT,
                                   FLOOR_KR,
                                   FLOOR_KT,
                                   FLOOR_IR);

    CheckedShader *checked_shader = new CheckedShader(FLOOR_A, FLOOR_B, FLOOR_C, FLOOR_D);
    r->setProceduralShader(checked_shader);
    scene->addShape(r);

    Sphere *sphere1 = new Sphere(SPHERE_1_CENTER, SPHERE_1_RADIUS,
                                SPHERE_1_AMBIENT,
                                SPHERE_1_DIFFUSE,
                                SPHERE_1_SPECULAR,
                                SPHERE_1_KA,
                                SPHERE_1_KD,
                                SPHERE_1_KS,
                                SPHERE_1_EXPONENT,
                                SPHERE_1_KR,
                                SPHERE_1_KT,
                                SPHERE_1_IR);
    scene->addShape(sphere1);

    // Create the second sphere
    Sphere *sphere2 = new Sphere(SPHERE_2_CENTER, SPHERE_2_RADIUS,
                                SPHERE_2_AMBIENT,
                                SPHERE_2_DIFFUSE,
                                SPHERE_2_SPECULAR,
                                SPHERE_2_KA,
                                SPHERE_2_KD,
                                SPHERE_2_KS,
                                SPHERE_2_EXPONENT,
                                SPHERE_2_KR,
                                SPHERE_2_KT,
                                SPHERE_2_IR);
    scene->addShape(sphere2);

    scene->addLight(new Light(LIGHT_1_POSITION, LIGHT_1_COLOR));

    return scene;
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
    open_scene("scene.txt", scene);

    run_raytracer();

    // OpenGL Dependency:

   	glutInit( &argc, argv );
   	glutInitDisplayMode( GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE );
   	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
   	glutInitWindowPosition(WINDOW_POS_X, WINDOW_POS_Y);
   	glutCreateWindow(WINDOW_TITLE);

	glLoadIdentity();
	gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);

   	// Callback functions
   	glutDisplayFunc( display );

   	glutMainLoop( );

   	return 0;

}



