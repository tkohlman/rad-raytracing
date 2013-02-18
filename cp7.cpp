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

#include <vector>
using namespace std;

#define WINDOW_TITLE "Ray Tracer - Checkpoint 4"

#define WINDOW_HEIGHT 550
#define WINDOW_WIDTH  700

#define WINDOW_POS_X  100
#define WINDOW_POS_Y  100

#define LMAX    1000
#define LDMAX   100

int lmax =  0;
int algo = 0;

#define DEPTH 3

void display( void ) {
    
    // Calculations to map locations to pixels
    float ratio = float(WINDOW_WIDTH)/WINDOW_HEIGHT;
    float dx = 2.0 * ratio / WINDOW_WIDTH;
    float dy = 2.0 / WINDOW_HEIGHT;
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
        new vector< vector<Color*>* >(WINDOW_HEIGHT, NULL);
    
    // Fire rays for every pixel
    for (int j = dy/2; j < WINDOW_HEIGHT; ++j) {
    
        pixels->at(j) = new vector<Color*>(WINDOW_WIDTH, NULL);
    
        for (int i = dx/2; i < WINDOW_WIDTH; ++i) {

            // Generate the ray
            Vector ray( (dx * i + xc), (dy * j + yc), -1);
            ray.Normalize();

            
            Color pixel = raytracer.Trace(ray, camera, 0);          
               
            // Set the color
            pixels->at(j)->at(i) = new Color(pixel);
        }
    }
    
    // Tone Reproduction Steps
    ToneReproducer tr(lmax, LDMAX, WINDOW_HEIGHT, WINDOW_WIDTH);
    tr.Run(pixels, algo);
    
    // Iterate over the pixels and render them.
    for (int j = dy/2; j < WINDOW_HEIGHT; ++j) {
        for (int i = dx/2; i < WINDOW_WIDTH; ++i) {
            
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

///
/// @name main
/// 
/// @description
/// 	Checkpoint 2 main program.
///
/// @param argc - number of command line arguments
/// @param argv - array of command line arguments
/// @return - program exit status
///
int main( int argc, char** argv ) {

    if (argc != 3) {
        cout << "Usage: cp7 <Lmax> <0(Ward)| 1(Reinhard)>" << endl;
        exit(1);
    }

    lmax = strtol(argv[1], NULL, 0);

    algo = strtof(argv[2], NULL);
    if (algo == 0)
        algo = WARDS;
    else
        algo = REINHARDS;

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



