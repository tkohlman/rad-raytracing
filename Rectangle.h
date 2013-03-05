///
/// @file Rectangle.h
///
/// @author	Thomas Kohlman
/// @date 27 December 2011
///
/// @description
/// 	Declares a rectangle from the Shape base class.
///

#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Shape.h"

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

    ///
    /// @name Intersect
    ///
    /// @description
    /// 	Determines if a ray intersects the rectangle.
    ///
    /// @param v - direction vector of the ray
    /// @param o - origin of the ray
    /// @return - intersection point closest to ray origin, NULL if no
    ///           intersection occurs
    ///
    Point* intersect(Vector v, Point o);

    ///
    /// @name GetSurfaceNormal
    ///
    /// @description
    /// 	Calculates the surface normal for a point on the
    ///     rectangle's surface.
    ///
    /// @param surface - a point on the rectangle's surface
    /// @return - the surface normal at this point on the rectangle
    ///
    Vector getSurfaceNormal(Point surface);

    const Point &getA() const { return _a; };
    const Point &getB() const { return _b; };
    const Point &getC() const { return _c; };
    const Point &getD() const { return _d; };

private:

    ///
    /// @name _a
    ///
    /// @description
    ///		The first point of the rectangle.
    ///
    Point _a;


    ///
    /// @name _b
    ///
    /// @description
    ///		The second point of the rectangle.
    ///
    Point _b;

    ///
    /// @name _c
    ///
    /// @description
    ///		The third point of the rectangle.
    ///
    Point _c;

    ///
    /// @name _d
    ///
    /// @description
    ///		The fourth point of the rectangle.
    ///
    Point _d;

    ///
    /// @name _normal
    ///
    /// @description
    ///		The vector normal to the plane formed by the rectangle.
    ///
    Vector _normal;

};  // class Rectangle

}   // namespace RadRt

#endif


