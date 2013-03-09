/*
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 */

#ifndef SPHERE_H
#define SPHERE_H

#include "shape.h"

namespace RadRt
{

class Sphere : public Shape
{
public:

    Sphere() {};
    ~Sphere() {};

    Json::Value serialize() const;
    void deserialize(const Json::Value &root);

    Point* intersect(const Ray &ray);

    ///
    /// @name GetSurfaceNormal
    ///
    /// @description
    /// 	Calculates the surface normal for a point on the sphere's surface.
    ///
    /// @param surface - a point on the sphere's surface
    /// @return - the surface normal at this point on the sphere
    ///
    Vector getSurfaceNormal(Point surface);

private:

    ///
    /// @name _center
    ///
    /// @description
    ///		The center point of the sphere.
    ///
    Point _center;

    ///
    /// @name _radius
    ///
    /// @description
    ///		The radius of the sphere.
    ///
    float _radius;

};  // class Sphere

}   // namespace RadRt

#endif



