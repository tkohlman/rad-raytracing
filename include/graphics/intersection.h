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

    Intersection(Point intersection_point,
                 Vector normal,
                 Shape *intersected_shape):
        m_intersection_point(intersection_point),
        m_normal(normal),
        m_intersected_shape(intersected_shape)
    {
    }

    Point intersection_point() const { return this->m_intersection_point; };
    Vector normal() const { return this->m_normal; };
    Shape *intersected_shape() const { return this->m_intersected_shape; };

    void set_normal(Vector normal) { this->m_normal = normal; };

private:

    Point m_intersection_point;
    Vector m_normal;
    Shape *m_intersected_shape;
};

}

#endif // INTERSECTION_H_INCLUDED
