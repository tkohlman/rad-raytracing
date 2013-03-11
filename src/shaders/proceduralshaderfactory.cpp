/*
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 */

#include "proceduralshaderfactory.h"
#include "checkedshader.h"

namespace RadRt
{

ProceduralShader *ProceduralShaderFactory:: create(std::string classname)
{
    if (classname.compare("checked_shader") == 0)
    {
        return new CheckedShader();
    }
    else
    {
        std::cerr << "Unknown Procedural Shader subclass: " << classname <<
            std::endl;
    }
    return nullptr;
}

}   // namespace RadRt
