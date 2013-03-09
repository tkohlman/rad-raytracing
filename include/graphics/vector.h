/*
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 */

#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>
#include <iostream>

#include "ijsonserializable.h"

namespace RadRt
{

class Vector : public IJsonSerializable
{

    friend inline Vector vectorAdd(const Vector &a, const Vector &b)
    {
        return Vector(a._x + b._x, a._y + b._y, a._z + b._z);
    }

    friend inline Vector normalize(const Vector &v)
    {
        double s = 1.0 / (double) sqrt(v._x * v._x + v._y * v._y + v._z * v._z);
        return Vector(v._x * s, v._y * s, v._z * s);
    }

    friend inline float length(const Vector &v)
    {
        return (float) sqrt(v._x * v._x + v._y * v._y + v._z * v._z);
    }

    friend inline Vector scalarMultiply( const Vector &v, const float scalar )
    {
        return Vector(v._x * scalar, v._y * scalar, v._z * scalar);
    }

    friend inline float dotProduct( const Vector &v1, const Vector &v2 )
    {
        return ((v1._x * v2._x) +
                (v1._y * v2._y) +
                (v1._z * v2._z));
    }

    friend inline Vector crossProduct( const Vector &v1, const Vector &v2 )
    {
        return Vector(v1._y * v2._z - v1._z * v2._y,
                      v1._z * v2._x - v1._x * v2._z,
                      v1._x * v2._y - v1._y * v2._x);
    }

    friend inline Vector vectorSubtract( const Vector &v1, const Vector &v2 )
    {
        return Vector(v1._x - v2._x, v1._y - v2._y, v1._z - v2._z);
    }

    friend inline Vector negateVector( const Vector &v )
    {
        return Vector(-v._x, -v._y, -v._z);
    }

public:

    ///
    /// @name Vector
    ///
    /// @description
    /// 	Constructor
    ///
    /// @param x - x-axis component of this vector
    /// @param y - y-axis component of this vector
    /// @param z - z-axis component of this vector
    /// @return - void
    ///
    Vector(float x, float y, float z);

    ///
    /// @name Vector
    ///
    /// @description
    /// 	Default constructor
    ///
    /// @return - void
    ///
    Vector();

    ///
    /// @name ~Vector
    ///
    /// @description
    /// 	Destructor
    ///
    /// @return - void
    ///
    ~Vector() {};

    Json::Value serialize() const;
    void deserialize(const Json::Value &root);

    inline float getX() const { return _x; };
    inline float getY() const { return _y; };
    inline float getZ() const { return _z; };

private:

    // XYZ Components
    float _x;
    float _y;
    float _z;


};  // class Vector

}   // namespace RadRt

#endif

