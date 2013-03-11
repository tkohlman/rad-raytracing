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

    Point* intersect(const Ray &ray, Vector **normal);

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


