#ifndef CHECKEDSHADER_H_INCLUDED
#define CHECKEDSHADER_H_INCLUDED

#include "proceduralshader.h"
#include "Rectangle.h"
using namespace Raytracer_n;

class CheckedShader : public ProceduralShader
{
public:

    CheckedShader( Point a, Point b, Point c, Point d );

    Color shade( const Point &p );

private:

    Point a;
    Point b;
    Point c;
    Point d;
};

#endif // CHECKEDSHADER_H_INCLUDED
