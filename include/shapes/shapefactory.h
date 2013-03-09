/*
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 */

#ifndef SHAPEFACTORY_H_INCLUDED
#define SHAPEFACTORY_H_INCLUDED

#include <string>
#include "shape.h"

namespace RadRt
{

class ShapeFactory
{
public:

    Shape *create(std::string classname);
};

}   // namespace RadRt

#endif // SHAPEFACTORY_H_INCLUDED
