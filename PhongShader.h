///
/// @file PhongShader.h
///
/// @author	Thomas Kohlman
/// @date 3 February 2012
///

#ifndef PHONG_SHADER_H
#define PHONG_SHADER_H

#include "Shape.h"
#include "Point.h"
#include <scene.h>

#include <vector>
using namespace std;

namespace Raytracer_n {

class PhongShader {

public:

    Color Shade(Scene *scene, Shape *object, Point intersection);

};  // class PhongShader

}   // namespace Raytracer_n

#endif




