/*
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 */

#ifndef RAY_H_INCLUDED
#define RAY_H_INCLUDED

#include "point.h"
#include "vector.h"

namespace RadRt
{

class Ray
{
public:

    Ray(Point vertex, Vector direction):
        vertex(vertex), direction(direction) {}

    Point getVertex() const { return vertex; };
    Vector getDirection() const { return direction; };

    void setVertex(Point vertex) { this->vertex = vertex; };
    void setDirection(Vector direction) { this->direction = direction; };

private:

    Point vertex;
    Vector direction;
};

}   // namespace RadRt

#endif // RAY_H_INCLUDED
