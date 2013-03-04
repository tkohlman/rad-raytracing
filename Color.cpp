///
/// @file Color.cpp
///
/// @author	Thomas Kohlman
/// @date 27 December 2011
///
/// @description
/// 	Implements an RGB color representation.
///

#include "Color.h"
using namespace Raytracer_n;

const Color Color::BLACK(0,0,0);

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

// ~Color
Color::~Color() {
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

// R
float Color::R() const {
    return (_r);
}

// G
float Color::G() const {
    return (_g);
}

// B
float Color::B() const {
    return (_b);
}

// operator=
Color& Color::operator=(const Color& other) {
    _r = other.R();
    _g = other.G();
    _b = other.B();
    return *this;
}

// operator<<
ostream& operator<<(ostream& os, const Color& color) {
    os << "(" << color.R() << "r, " << color.G() << "g, " << color.B() << "b)";
    return os;
}




