///
/// @file PhongShader.h
///
/// @author	Thomas Kohlman
/// @date 3 February 2012
///

#ifndef PHONG_SHADER_H
#define PHONG_SHADER_H

#include "shape.h"
#include "point.h"
#include "scene.h"

namespace RadRt
{

class PhongShader
{
public:

    Color shade(Scene *scene, Shape *object, Point intersection);

};  // class PhongShader

}   // namespace RadRt

#endif




