/*
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 */

#ifndef POINT_H
#define POINT_H

#include "vector.h"
#include "color.h"

#include <ijsonserializable.h>

namespace RadRt
{

class Point
{
    friend inline float distanceBetween( const Point &p1, const Point &p2 )
    {
        float dx = p1._x - p2._x;
        float dy = p1._y - p2._y;
        float dz = p1._z - p2._z;

        return sqrt((dx*dx) + (dy*dy) + (dz*dz));
    }

    friend inline Vector displacementVector( const Point &p1, const Point &p2 )
    {
        return Vector(p1._x - p2._x, p1._y - p2._y, p1._z - p2._z);
    }

public:

    ///
    /// @name Point
    ///
    /// @description
    /// 	Constructor
    ///
    /// @param x - x-axis component of constructed point
    /// @param y - y-axis component of constructed point
    /// @param z - z-axis component of constructed point
    ///
    Point(float x, float y, float z);

    ///
    /// @name Point
    ///
    /// @description
    /// 	Constructor
    ///
    /// @param p - starting point
    /// @param v - direction vector
    /// @param distance - distance along direction vector
    ///
    Point(const Point& p, const Vector& v, const float& distance);

    ///
    /// @name Point
    ///
    /// @description
    /// 	Copy Constructor
    ///
    /// @param other - Point object to copy
    ///
    Point(const Point& other);

    ///
    /// @name Point
    ///
    /// @description
    /// 	Default Constructor
    ///
    Point();

    ~Point() {};

    float getX() const { return _x; };
    float getY() const { return _y; };
    float getZ() const { return _z; };

    Json::Value serialize() const;
    void deserialize(const Json::Value &root);

private:

    float _x;
    float _y;
    float _z;

};  // class Point

}   // namespace RadRt

#endif
