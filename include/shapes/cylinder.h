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
    /// @return - void
    ///
    ~Cylinder();

    Json::Value serialize() const;
    void deserialize(const Json::Value &root);

    virtual Point* intersect(const Ray &ray, Vector **normal);

private:

    ///
    /// @name _cp1
    ///
    /// @description
    ///		The center point of the first base of the cylinder.
    ///
    Point _cp1;

    ///
    /// @name _cp2
    ///
    /// @description
    ///		The center point of the second base of the cylinder.
    ///
    Point _cp2;

    ///
    /// @name _radius
    ///
    /// @description
    ///		The radius of the cylinder.
    ///
    float _radius;

    ///
    /// @name _orient
    ///
    /// @description
    ///		The vector (orientation) formed by the two center points.
    ///
    Vector _orient;

};  // class Cylinder

}   // namespace RadRt

#endif // CYLINDER_H_INCLUDED
