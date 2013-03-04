


#include <proceduralshaderfactory.h>
#include <checkedshader.h>

ProceduralShader *ProceduralShaderFactory:: create(std::string classname)
{
    if (classname.compare("checked_shader") == 0)
    {
        return new CheckedShader();
    }
    else
    {
        cerr << "Unknown Procedural Shader subclass: " << classname << endl;
    }
    return NULL;
}
