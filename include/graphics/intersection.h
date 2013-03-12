/*
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 */

#ifndef INTERSECTION_H_INCLUDED
#define INTERSECTION_H_INCLUDED

#include "point.h"
#include "shape.h"
#include "vector.h"

namespace RadRt
{

class Intersection
{
public:

    Intersection(Point intersectionPoint, Vector normal,
                 Shape *intersectedShape):
        intersectionPoint(intersectionPoint),
        normal(normal),
        intersectedShape(intersectedShape) {}

    Point getIntersectionPoint() const { return this->intersectionPoint; };
    Vector getNormal() const { return this->normal; };
    Shape *getIntersectedShape() const { return this->intersectedShape; };

    void setNormal(Vector normal) { this->normal = normal; };

private:

    Point intersectionPoint;
    Vector normal;
    Shape *intersectedShape;
};

}

#endif // INTERSECTION_H_INCLUDED
