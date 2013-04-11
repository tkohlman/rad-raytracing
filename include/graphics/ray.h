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
        m_vertex(vertex), m_direction(direction) {}

    Point vertex() const { return m_vertex; };
    Vector direction() const { return m_direction; };

    void set_vertex(Point vertex) { this->m_vertex = vertex; };
    void set_direction(Vector direction) { this->m_direction = direction; };

private:

    Point m_vertex;
    Vector m_direction;
};

}   // namespace RadRt

#endif // RAY_H_INCLUDED
