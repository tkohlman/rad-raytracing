#ifndef PROCEDURALSHADERFACTORY_H_INCLUDED
#define PROCEDURALSHADERFACTORY_H_INCLUDED

#include <proceduralshader.h>
#include <string.h>

class ProceduralShaderFactory
{
public:
    ProceduralShader *create(std::string classname);
};

#endif // PROCEDURALSHADERFACTORY_H_INCLUDED
