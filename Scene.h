///
/// @file scene.h
/// 
/// @author	Thomas Kohlman
/// @date 27 February 2012
///
/// @description
/// 	Contains macros to define the scene.
///
/// Version:
/// 	$Id$
/// 
/// Revisions:
///		$Log$
///
///

#ifndef SCENE_H
#define SCENE_H

// Camera Constants
#define CAMERA_POSITION Point(0, 1.5, 5)

// Floor Constants
#define FLOOR_A Point(-32, -12, 0)
#define FLOOR_B Point(-32, -12, -72)
#define FLOOR_C Point(16, -12, -72)
#define FLOOR_D Point(16, -12, 0)

#define FLOOR_AMBIENT   Color(1, 0, 0)
#define FLOOR_DIFFUSE   Color(1, 0, 0)
#define FLOOR_SPECULAR  Color(1, 1, 1)
#define FLOOR_EXPONENT  8
#define FLOOR_KA        0.25
#define FLOOR_KD        0.75
#define FLOOR_KS        1.00
#define FLOOR_KR        0.00
#define FLOOR_KT        0.00
#define FLOOR_IR        0.00

// Light Source Constants
#define LIGHT_1_POSITION    Point(1, 8, 0)
#define LIGHT_1_COLOR       Color(1, 1, 1)

// Sphere 1 Constants
#define SPHERE_1_RADIUS 4
#define SPHERE_1_CENTER Point(0, 0, -10)

#define SPHERE_1_AMBIENT    Color(1, 1, 1)
#define SPHERE_1_DIFFUSE    Color(1, 1, 1)
#define SPHERE_1_SPECULAR   Color(1, 1, 1)
#define SPHERE_1_EXPONENT   20
#define SPHERE_1_KA         0.075
#define SPHERE_1_KD         0.075
#define SPHERE_1_KS         0.2
#define SPHERE_1_KR         0.01
#define SPHERE_1_KT         0.85
#define SPHERE_1_IR         0.95

// Sphere 2 Constants
#define SPHERE_2_RADIUS 4
#define SPHERE_2_CENTER Point(-6, -4, -16)

#define SPHERE_2_AMBIENT    Color(0.7, 0.7, 0.7)
#define SPHERE_2_DIFFUSE    Color(0.7, 0.7, 0.7)
#define SPHERE_2_SPECULAR   Color(1, 1, 1)
#define SPHERE_2_EXPONENT   20
#define SPHERE_2_KA         0.15
#define SPHERE_2_KD         0.25
#define SPHERE_2_KS         1.00
#define SPHERE_2_KR         0.75
#define SPHERE_2_KT         0.00
#define SPHERE_2_IR         0.00

// Background Color
#define BACKGROUND_COLOR Color(0.0, 0.65, 0.90)

// World Ambient Light
#define WORLD_AMBIENT Color(1, 1, 1)


#endif




