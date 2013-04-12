/*
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 */

#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.h"

namespace RadRt
{

class Rectangle : public Shape
{
public:

    Rectangle() {};
    ~Rectangle() {};

    void init();

    Json::Value serialize() const;
    void deserialize(const Json::Value &root);

    Ray *intersect(const Ray &ray);

    const Point3d &a() const { return m_a; };
    const Point3d &b() const { return m_b; };
    const Point3d &c() const { return m_c; };
    const Point3d &d() const { return m_d; };

private:

    Point3d m_a;
    Point3d m_b;
    Point3d m_c;
    Point3d m_d;

    Vector3d m_normal;

};  // class Rectangle

}   // namespace RadRt

#endif
