/*
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 */

#ifndef RAY_H_INCLUDED
#define RAY_H_INCLUDED

#include "point3d.h"
#include "vector3d.h"

namespace RadRt
{

class Ray
{
public:

    Ray(Point3d vertex, Vector3d direction):
        m_vertex(vertex), m_direction(direction) {}

    Point3d vertex() const { return m_vertex; };
    Vector3d direction() const { return m_direction; };

    void set_vertex(Point3d vertex) { this->m_vertex = vertex; };
    void set_direction(Vector3d direction) { this->m_direction = direction; };

private:

    Point3d m_vertex;
    Vector3d m_direction;
};

}   // namespace RadRt

#endif // RAY_H_INCLUDED
