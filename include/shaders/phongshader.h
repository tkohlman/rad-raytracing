/*
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 */

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




