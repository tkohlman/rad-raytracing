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

    CheckedShader( Point a, Point b, Point c, Point d );

    CheckedShader() {};

    Color shade( const Point &p );

    Json::Value serialize() const;
    void deserialize(const Json::Value &root);

private:

    Point m_a;
    Point m_b;
    Point m_c;
    Point m_d;
};

}   // namespace RadRt

#endif // CHECKEDSHADER_H_INCLUDED
