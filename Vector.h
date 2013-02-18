///
/// @file Vector.h
/// 
/// @author	Thomas Kohlman
/// @date 27 December 2011
///
/// @description
/// 	Declares a vector representation.
///
/// Version:
/// 	$Id: Vector.h,v 1.3 2012/01/21 17:39:00 thomas Exp thomas $
/// 
/// Revisions:
///		$Log: Vector.h,v $
///		Revision 1.3  2012/01/21 17:39:00  thomas
///		Checkpoint 3, working baseline.
///
///		Revision 1.2  2011/12/28 18:47:49  thomas
///		Checkpoint 2, functioning baseline.
///
///		Revision 1.1  2011/12/27 18:05:43  thomas
///		Initial revision
///
///
///

#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>
#include <iostream>
using namespace std;

namespace Raytracer_n {

class Vector {

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
    
    friend inline Vector operator+(const Vector& a, const Vector& b) {
        return Vector(a.X() + b.X(), a.Y() + b.Y(), a.Z() + b.Z());
    }
    
    friend inline Vector operator*(float scalar, const Vector& v) {
        return Vector(v._x * scalar, v._y * scalar, v._z * scalar);
    }
    
    friend inline Vector Normalize(const Vector& v) {
        double s = 1.0 / (double) sqrt(v._x * v._x + v._y * v._y + v._z * v._z);
        return Vector(v._x * s, v._y * s, v._z * s);
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
    ~Vector();
    
    ///
    /// @name Normalize
    /// 
    /// @description
    /// 	Normalizes the vector to a unit length.
    ///
    /// @return - void
    ///    
    inline void Normalize();
    
    ///
    /// @name Length
    /// 
    /// @description
    /// 	Returns the length of the vector
    ///
    /// @return - void
    ///    
    inline float Length();
    
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
    
    ///
    /// @name operator*
    /// 
    /// @description
    /// 	Scalar multiplication operator.
    ///
    /// @param scalar - scalar multiplier
    /// @return - Vector multiplied by scalar value
    ///
    inline Vector operator*(const float& scalar) const;
    
    ///
    /// @name operator*
    /// 
    /// @description
    /// 	Dot product operator.
    ///
    /// @param other - the second vector
    /// @return - Vector dot product
    ///
    inline float operator*(const Vector& other) const;

    ///
    /// @name operator^
    /// 
    /// @description
    /// 	Cross product operator.
    ///
    /// @param other - the second vector
    /// @return - Vector cross product
    ///
    inline Vector operator^(const Vector& other) const;
    
    ///
    /// @name operator=
    /// 
    /// @description
    /// 	Equals operator.
    ///
    /// @param other - the second vector
    /// @return - address of this argument
    ///
    inline Vector& operator=(const Vector& other);
    
    ///
    /// @name operator*=
    /// 
    /// @description
    /// 	Times-equals operator.
    ///
    /// @param s - a scalar floating point value
    /// @return - address of this argument
    ///
    inline Vector& operator*=(float s);
    
    ///
    /// @name operator-
    /// 
    /// @description
    /// 	Negation operator.
    ///
    /// @return - negation of this vector
    ///
    inline Vector operator-() const;
    
    inline Vector operator-(const Vector& other);

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

// Normalize
inline void Vector::Normalize() {
    double s = 1.0 / (double) sqrt(_x * _x + _y * _y + _z * _z);
    _x *= s; _y *= s; _z *= s;
}

//
// Length
//
float Vector::Length() {
    return (float) sqrt(_x * _x + _y * _y + _z * _z);
}

// X   
inline float Vector::X() const {
    return (_x);
}

// Y  
inline float Vector::Y() const {
    return (_y);
}

// Z  
inline float Vector::Z() const {
    return (_z);
}

// operator*
inline Vector Vector::operator*(const float& scalar) const {
    return Vector(_x * scalar, _y * scalar, _z * scalar);
}

// operator*
inline float Vector::operator*(const Vector& other) const {
    return (_x * other.X() + _y * other.Y() + _z * other.Z());
}

// operator^
inline Vector Vector::operator^(const Vector& other) const {
    return Vector(_y * other.Z() - _z * other.Y(),
                  _z * other.X() - _x * other.Z(),
                  _x * other.Y() - _y * other.X());
}

// operator=
inline Vector& Vector::operator=(const Vector& other) {
    _x = other.X();
    _y = other.Y();
    _z = other.Z();
    return *this;
}

// operator*=
inline Vector& Vector::operator*=(float s) {
    _x *= s;
    _y *= s;
    _z *= s;
    return *this;
}

inline Vector Vector::operator-() const {
    return Vector(-_x, -_y, -_z);
}

inline Vector Vector::operator-(const Vector& other) {
  return Vector(_x - other._x, _y - other._y, _z - other._z);
}

}   // namespace Raytracer_n

#endif

