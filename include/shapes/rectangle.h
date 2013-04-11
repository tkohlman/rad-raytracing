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

    const Point &a() const { return m_a; };
    const Point &b() const { return m_b; };
    const Point &c() const { return m_c; };
    const Point &d() const { return m_d; };

private:

    Point m_a;
    Point m_b;
    Point m_c;
    Point m_d;

    Vector m_normal;

};  // class Rectangle

}   // namespace RadRt

#endif
