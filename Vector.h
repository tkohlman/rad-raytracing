///
/// @file Vector.h
///
/// @author	Thomas Kohlman
/// @date 27 December 2011
///
/// @description
/// 	Declares a vector representation.
///

#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>
#include <iostream>
using namespace std;

#include <ijsonserializable.h>

namespace Raytracer_n {

class Vector : public IJsonSerializable
{

    ///
    /// @name operator<<
    ///
    /// @description
    /// 	Vector output operator.
    ///
    /// @param os - the output stream
    /// @param other - the vector to output
    /// @return - the output stream
    ///
    friend ostream& operator<<(ostream& os, const Vector& other);

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

    ///
    /// @name X
    ///
    /// @description
    /// 	Accessor for _x member variable.
    ///
    /// @return - x-axis component of this vector
    ///
    inline float X() const;

    ///
    /// @name Y
    ///
    /// @description
    /// 	Accessor for _y member variable.
    ///
    /// @return - y-axis component of this vector
    ///
    inline float Y() const;

    ///
    /// @name Z
    ///
    /// @description
    /// 	Accessor for _z member variable.
    ///
    /// @return - z-axis component of this vector
    ///
    inline float Z() const;

private:

    ///
    /// @name _x
    ///
    /// @description
    ///		The x-axis component of this vector.
    ///
    float _x;

    ///
    /// @name _y
    ///
    /// @description
    ///		The y-axis component of this vector.
    ///
    float _y;

    ///
    /// @name _z
    ///
    /// @description
    ///		The z-axis component of this vector.
    ///
    float _z;


};  // class Vector

inline float Vector::X() const {
    return (_x);
}

inline float Vector::Y() const {
    return (_y);
}

inline float Vector::Z() const {
    return (_z);
}

}   // namespace Raytracer_n

#endif

