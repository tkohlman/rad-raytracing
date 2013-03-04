#ifndef SHAPEFACTORY_H_INCLUDED
#define SHAPEFACTORY_H_INCLUDED

#include <string>
#include <Shape.h>

class ShapeFactory
{
public:

    Shape *create(std::string classname);
};

#endif // SHAPEFACTORY_H_INCLUDED
