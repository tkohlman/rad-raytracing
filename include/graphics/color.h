/*
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 */

#ifndef COLOR_H
#define COLOR_H

#include <iostream>

#include "ijsonserializable.h"

namespace RadRt
{

class Color : public IJsonSerializable
{
public:

    ///
    /// @name Color
    ///
    /// @description
    /// 	Constructor
    ///
    /// @param r - the red component of the constructed color
    /// @param g - the green component of the constructed color
    /// @param b - the blue component of the constructed color
    /// @return <returns>
    ///
    Color(float r, float g, float b);

    ///
    /// @name Color
    ///
    /// @description
    /// 	Copy constructor
    ///
    /// @param other - Color object to copy
    /// @return - void
    ///
    Color(const Color& other);

    ///
    /// @name Color
    ///
    /// @description
    /// 	Default constructor
    ///
    /// @return - void
    ///
    Color();

    ///
    /// @name ~Color
    ///
    /// @description
    /// 	Destructor
    ///
    /// @return - void
    ///
    ~Color() {};

    Json::Value serialize() const;
    void deserialize(const Json::Value &root);

    float getR() const { return _r; };
    float getG() const { return _g; };
    float getB() const { return _b; };

    inline void clamp();

    inline Color operator*(const Color& other);

    inline Color operator*(float scalar);

    inline Color& operator*=(float scalar);

    inline Color operator/(float scalar);

    inline Color& operator/=(float scalar);

    inline Color operator+(const Color& other);

    inline Color& operator+=(const Color& other);

    const static Color BLACK;
    const static Color BLUE;
    const static Color GREEN;
    const static Color CYAN;
    const static Color RED;
    const static Color PURPLE;
    const static Color YELLOW;
    const static Color WHITE;

private:

    // RGB Components
    float _r;
    float _g;
    float _b;

};  // class Color

//
// operator*
//
inline Color Color::operator*(const Color& other) {
    return Color(_r * other._r, _g * other._g, _b * other._b);
}

//
// operator*
//
inline Color Color::operator*(float scalar) {
    return Color(_r * scalar, _g * scalar, _b * scalar);
}

//
// operator*=
//
inline Color& Color::operator*=(float scalar) {
    _r *= scalar;
    _g *= scalar;
    _b *= scalar;
    return *this;
}

//
// operator/
//
inline Color Color::operator/(float scalar) {

    if (scalar != 0)
        return Color(_r / scalar, _g / scalar, _b / scalar);
    else
        return Color(_r, _g, _b);
}

//
// operator/=
//
inline Color& Color::operator/=(float scalar) {

    if (scalar != 0) {
        _r /= scalar;
        _g /= scalar;
        _b /= scalar;
    }
    return *this;
}

//
// operator+
//
inline Color Color::operator+(const Color& other) {
    return Color(_r + other._r, _g + other._g, _b + other._b);
}

//
// operator+=
//
inline Color& Color::operator+=(const Color& other) {
    _r += other._r;
    _g += other._g;
    _b += other._b;
    return *this;
}

//
// Clamp
//
inline void Color::clamp() {
    if (_r > 1.0) {
        _r = 1.0;
    }
    if (_g > 1.0) {
        _g = 1.0;
    }
    if (_b > 1.0) {
        _b = 1.0;
    }
}

}   // namespace RadRt

#endif



