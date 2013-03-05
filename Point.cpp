///
/// @file Point.cpp
///
/// @author	Thomas Kohlman
/// @date 27 December 2011
///
/// @description
/// 	Implements a 3D point representation.
///

#include "Point.h"
using namespace Raytracer_n;

Point::Point(float x, float y, float z)
{
    _x = x;
    _y = y;
    _z = z;
}

Point::Point(const Point& other)
{
    _x = other._x;
    _y = other._y;
    _z = other._z;
}

Point::Point(const Point& p, const Vector& v, const float& distance)
{
    _x = p._x + v.getX() * distance;
    _y = p._y + v.getY() * distance;
    _z = p._z + v.getZ() * distance;
}

Point::Point()
{
    _x = _y = _z = 0;
}

Json::Value Point::serialize() const
{
    Json::Value root;
    root["x"] = _x;
    root["y"] = _y;
    root["z"] = _z;
    return root;
}

void Point::deserialize(const Json::Value &root)
{
    _x = root["x"].asFloat();
    _y = root["y"].asFloat();
    _z = root["z"].asFloat();
}
