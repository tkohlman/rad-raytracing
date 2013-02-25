///
/// @file Point.cpp
///
/// @author	Thomas Kohlman
/// @date 27 December 2011
///
/// @description
/// 	Implements a 3D point representation.
///
/// Version:
/// 	$Id: Point.cpp,v 1.4 2012/01/21 17:39:00 thomas Exp thomas $
///
/// Revisions:
///		$Log: Point.cpp,v $
///		Revision 1.4  2012/01/21 17:39:00  thomas
///		Checkpoint 3, working baseline.
///
///		Revision 1.3  2011/12/28 19:52:52  thomas
///		Checkpoint 2, genericized shape handling.
///
///		Revision 1.2  2011/12/28 18:47:18  thomas
///		Checkpoint 2, functioning baseline.
///
///		Revision 1.1  2011/12/27 18:37:46  thomas
///		Initial revision
///
///
///

#include "Point.h"
using namespace Raytracer_n;

// Point
Point::Point(float x, float y, float z) :
    _x(x), _y(y), _z(z) {
}

// Point
Point::Point(const Point& other) :
    _x(other._x), _y(other._y), _z(other._z) {
}

// Constructor
Point::Point(const Point& p, const Vector& v, const float& distance) {

    if (distance != 0) {
        _x = p.X() + v.X() * distance;
        _y = p.Y() + v.Y() * distance;
        _z = p.Z() + v.Z() * distance;
    } else {
        _x = p.X();
        _y = p.Y();
        _z = p.Z();
    }
}

// Point
Point::Point() :
    _x(0), _y(0), _z(0) {
}

// ~Point
Point::~Point() {
}

// X
float Point::X() const {
    return (_x);
}

// Y
float Point::Y() const {
    return (_y);
}

// Z
float Point::Z() const {
    return (_z);
}

