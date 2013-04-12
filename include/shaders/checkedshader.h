/*
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 */

#ifndef CHECKEDSHADER_H_INCLUDED
#define CHECKEDSHADER_H_INCLUDED

#include "proceduralshader.h"
#include "rectangle.h"

namespace RadRt
{

class CheckedShader : public ProceduralShader
{
public:

    CheckedShader( Point3d a, Point3d b, Point3d c, Point3d d );

    CheckedShader() {};

    Color shade( const Point3d &p );

    Json::Value serialize() const;
    void deserialize(const Json::Value &root);

private:

    Point3d m_a;
    Point3d m_b;
    Point3d m_c;
    Point3d m_d;
};

}   // namespace RadRt

#endif // CHECKEDSHADER_H_INCLUDED
