#ifndef PROCEDURALSHADERFACTORY_H_INCLUDED
#define PROCEDURALSHADERFACTORY_H_INCLUDED

#include "proceduralshader.h"
#include <string.h>

namespace RadRt
{

class ProceduralShaderFactory
{
public:
    ProceduralShader *create(std::string classname);
};

}   // namespace RadRt

#endif // PROCEDURALSHADERFACTORY_H_INCLUDED
