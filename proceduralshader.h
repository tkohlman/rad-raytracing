#ifndef PROCEDURALSHADER_H
#define PROCEDURALSHADER_H

#include "Color.h"
#include "Point.h"
using namespace Raytracer_n;

#include <ijsonserializable.h>

class ProceduralShader : public IJsonSerializable
{
public:

    virtual Color shade( const Point &p ) = 0;
};

#endif // PROCEDURALSHADER_H
