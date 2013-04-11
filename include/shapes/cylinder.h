/*
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 */

#ifndef CYLINDER_H_INCLUDED
#define CYLINDER_H_INCLUDED

#include "shape.h"

namespace RadRt
{

class Cylinder : public Shape
{
public:

    Cylinder() {};

    void init();

    ///
    /// @name ~Cylinder
    ///
    /// @description
    /// 	Destructor
    ///
    ~Cylinder();

    Json::Value serialize() const;
    void deserialize(const Json::Value &root);

    Ray *intersect(const Ray &ray);

private:

    Point m_center_point_1;
    Point m_center_point_2;

    float m_radius;

    Vector m_orientation;

};  // class Cylinder

}   // namespace RadRt

#endif // CYLINDER_H_INCLUDED
