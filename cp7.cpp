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
#include "Sphere.h"
#include "Light.h"
#include "World.h"
#include "Raytracer.h"
#include "PhongShader.h"
#include "ToneReproducer.h"
#include "Scene.h"

using namespace Raytracer_n;
#include "scene.h"

#include <vector>
#include <unistd.h>
using namespace std;

#define WINDOW_TITLE "Ray Tracer - Checkpoint 7"

#define WINDOW_HEIGHT 550
#define WINDOW_WIDTH  700

#define WINDOW_POS_X  100
#define WINDOW_POS_Y  100

#define LMAX    1000
#define LDMAX   100

int aflag = 0;      /* specify tone reproduction algorithm */
int bflag = 0;      /* specify the number of bounces */
int fflag = 0;      /* specify output file format */
int lflag = 0;      /* specify lmax value for tone reproduction */
int oflag = 0;      /* specify output file */
int sflag = 0;      /* scecify a sence.obj file to render */

int lmax =  0;
int algo = 0;

#define DEPTH 3

void display( void ) {

    Scene scene( WINDOW_WIDTH, WINDOW_HEIGHT );

    // Calculations to map locations to pixels
    float ratio = float(scene.getWidth())/scene.getHeight();
    float dx = 2.0 * ratio / scene.getWidth();
    float dy = 2.0 / scene.getHeight();
    float z = -1;
    float xc = -ratio;
    float yc = -1;

    // Create the world
    World world(WORLD_AMBIENT);

    // Create a vector of shapes
    vector<Shape*> shapes;

    // Create the rectangle (floor)
    shapes.push_back(new Rectangle(FLOOR_A, FLOOR_B, FLOOR_C, FLOOR_D,
                                   FLOOR_AMBIENT,
                                   FLOOR_DIFFUSE,
                                   FLOOR_SPECULAR,
                                   FLOOR_KA,
                                   FLOOR_KD,
                                   FLOOR_KS,
                                   FLOOR_EXPONENT,
                                   FLOOR_KR,
                                   FLOOR_KT,
                                   FLOOR_IR));

    // Create the first sphere
    shapes.push_back(new Sphere(SPHERE_1_CENTER, SPHERE_1_RADIUS,
                                SPHERE_1_AMBIENT,
                                SPHERE_1_DIFFUSE,
                                SPHERE_1_SPECULAR,
                                SPHERE_1_KA,
                                SPHERE_1_KD,
                                SPHERE_1_KS,
                                SPHERE_1_EXPONENT,
                                SPHERE_1_KR,
                                SPHERE_1_KT,
                                SPHERE_1_IR));

    // Create the second sphere
    shapes.push_back(new Sphere(SPHERE_2_CENTER, SPHERE_2_RADIUS,
                                SPHERE_2_AMBIENT,
                                SPHERE_2_DIFFUSE,
                                SPHERE_2_SPECULAR,
                                SPHERE_2_KA,
                                SPHERE_2_KD,
                                SPHERE_2_KS,
                                SPHERE_2_EXPONENT,
                                SPHERE_2_KR,
                                SPHERE_2_KT,
                                SPHERE_2_IR));

    // Create a vector of lights
    vector<Light> lights;

    // Create light 1
    lights.push_back(Light(LIGHT_1_POSITION, LIGHT_1_COLOR));

    PhongShader shader(lights, shapes, world);

    // Instantiate the camera position
    Point camera = CAMERA_POSITION;

    // Create the raytracer
    Raytracer raytracer(DEPTH, BACKGROUND_COLOR, shader, shapes);

    // Create the pixels array.
    vector< vector<Color*>* > *pixels =
        new vector< vector<Color*>* >(scene.getHeight(), NULL);

    // Fire rays for every pixel
    for (int j = dy/2; j < scene.getHeight(); ++j) {

        pixels->at(j) = new vector<Color*>(scene.getWidth(), NULL);

        for (int i = dx/2; i < scene.getWidth(); ++i) {

            // Generate the ray
            Vector ray( (dx * i + xc), (dy * j + yc), -1);
            ray.Normalize();


            Color pixel = raytracer.Trace(ray, camera, 0);

            // Set the color
            pixels->at(j)->at(i) = new Color(pixel);
        }
    }

    if (aflag && lflag)
    {
        // Tone Reproduction Steps
        ToneReproducer tr(lmax, LDMAX, scene.getHeight(), scene.getWidth());
        tr.Run(pixels, algo);
    }

    // Iterate over the pixels and render them.
    for (int j = dy/2; j < scene.getHeight(); ++j) {
        for (int i = dx/2; i < scene.getWidth(); ++i) {

            float r_comp = pixels->at(j)->at(i)->R();
            float g_comp = pixels->at(j)->at(i)->G();
            float b_comp = pixels->at(j)->at(i)->B();

            // Set the color
            glColor3f(r_comp, g_comp, b_comp);

            // Draw the point
            glBegin(GL_POINTS);
	        glVertex2i(i, j);
            glEnd();
        }
    }

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
	while ((op = getopt(argc, argv, "a:b:f:l:o:s:")) != -1)
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
            cout << "Warning: b flag not yet implemented" << endl;
            break;

		case 'f':
			++fflag;
			cout << "Warning: f flag not yet implemented" << endl;
			break;

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



