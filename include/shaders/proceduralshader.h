/*
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 */

#ifndef PROCEDURALSHADER_H
#define PROCEDURALSHADER_H

#include "color.h"
#include "point3d.h"
#include "ijsonserializable.h"

namespace RadRt
{

class ProceduralShader : public IJsonSerializable
{
public:

    virtual Color shade( const Point3d &p ) = 0;
};

}   // namespace RadRt

#endif // PROCEDURALSHADER_H
