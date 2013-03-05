///
/// @file Vector.cpp
///
/// @author	Thomas Kohlman
/// @date 27 December 2011
///
/// @description
/// 	Implements a vector representation.
///
/// Version:
/// 	$Id: Vector.cpp,v 1.3 2012/01/21 17:39:00 thomas Exp thomas $
///
/// Revisions:
///		$Log: Vector.cpp,v $
///		Revision 1.3  2012/01/21 17:39:00  thomas
///		Checkpoint 3, working baseline.
///
///		Revision 1.2  2011/12/28 18:47:18  thomas
///		Checkpoint 2, functioning baseline.
///
///		Revision 1.1  2011/12/27 18:13:36  thomas
///		Initial revision
///
///
///

#include "Vector.h"
using namespace Raytracer_n;

#include <iostream>
using namespace std;

Vector::Vector(float x, float y, float z)
{
    _x = x;
    _y = y;
    _z = z;
}

Vector::Vector()
{
    _x = _y = _z = 0;
}

Json::Value Vector::serialize() const
{
    Json::Value root;
    root["x"] = _x;
    root["y"] = _y;
    root["z"] = _z;
    return root;
}

void Vector::deserialize(const Json::Value &root)
{
    _x = root["x"].asFloat();
    _y = root["y"].asFloat();
    _z = root["z"].asFloat();
}

namespace Raytracer_n {
ostream& operator<<(ostream& os, const Vector& other) {
    os << "(" << other.getX() << "i, " << other.getY() << "j, " << other.getZ() << "k)";
    return os;
}

}

