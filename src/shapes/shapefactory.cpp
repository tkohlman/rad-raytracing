/*
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 */

#include "shapefactory.h"
#include "cylinder.h"
#include "rectangle.h"
#include "sphere.h"
#include <iostream>

namespace RadRt
{

Shape *ShapeFactory::create(std::string classname)
{
    if (classname.compare("rectangle") == 0)
    {
        return new Rectangle();
    }
    else if (classname.compare("sphere") == 0)
    {
        return new Sphere();
    }
    else if (classname.compare("cylinder") == 0)
    {
        return new Cylinder();
    }
    else
    {
        std::cerr << "Unknown Shape subclass: " << classname << std::endl;
    }
    return NULL;
}

}   // namespace RadRt
