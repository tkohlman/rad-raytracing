/*
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 */

#include "color.h"

namespace RadRt
{

const Color Color::BLACK(0,0,0);
const Color Color::BLUE(0,0,1);
const Color Color::GREEN(0,1,0);
const Color Color::CYAN(0,1,1);
const Color Color::RED(1,0,0);
const Color Color::PURPLE(1,0,1);
const Color Color::YELLOW(1,1,0);
const Color Color::WHITE(1,1,1);

// Color
Color::Color(float r, float g, float b) :
    _r(r), _g(g), _b(b) {
}

// Color
Color::Color(const Color& other) :
    _r(other._r), _g(other._g), _b(other._b) {
}

// Color
Color::Color() :
    _r(0), _g(0), _b(0) {
}

Json::Value Color::serialize() const
{
    Json::Value root;
    root["r"] = _r;
    root["g"] = _g;
    root["b"] = _b;
    return root;
}

void Color::deserialize(const Json::Value &root)
{
    _r = root["r"].asFloat();
    _g = root["g"].asFloat();
    _b = root["b"].asFloat();
}

}   // namespace RadRt


