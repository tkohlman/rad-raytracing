
#include <ShapeFactory.h>
#include <cylinder.h>
#include <Rectangle.h>
#include <Sphere.h>
#include <iostream>

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
        cerr << "Unknown Shape subclass: " << classname << endl;
    }
}
