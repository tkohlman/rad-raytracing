#ifndef CHECKEDSHADER_H_INCLUDED
#define CHECKEDSHADER_H_INCLUDED

#include "proceduralshader.h"
#include "Rectangle.h"
using namespace Raytracer_n;

class CheckedShader : public ProceduralShader
{
public:

    CheckedShader( Point a, Point b, Point c, Point d );

    CheckedShader() {};

    Color shade( const Point &p );

    Json::Value serialize() const;
    void deserialize(const Json::Value &root);

private:

    Point a;
    Point b;
    Point c;
    Point d;
};

#endif // CHECKEDSHADER_H_INCLUDED
