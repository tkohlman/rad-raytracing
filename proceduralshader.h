#ifndef PROCEDURALSHADER_H
#define PROCEDURALSHADER_H

#include "Color.h"
#include "Point.h"
#include <ijsonserializable.h>

namespace RadRt
{

class ProceduralShader : public IJsonSerializable
{
public:

    virtual Color shade( const Point &p ) = 0;
};

}   // namespace RadRt

#endif // PROCEDURALSHADER_H
