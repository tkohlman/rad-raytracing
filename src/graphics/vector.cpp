/*
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 */

#include "vector.h"

namespace RadRt
{

Vector::Vector(float x, float y, float z):
    _x(x),
    _y(y),
    _z(z)
{
}

Vector::Vector():
    _x(0),
    _y(0),
    _z(0)
{
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

}   // namespace RadRt
