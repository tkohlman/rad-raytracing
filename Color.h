///
/// @file Color.h
///
/// @author	Thomas Kohlman
/// @date 23 December 2011
///
/// @description
/// 	Declares an RGB Color representation.
///
/// Version:
/// 	$Id: Color.h,v 1.4 2012/01/21 17:36:56 thomas Exp thomas $
///
/// Revisions:
///		$Log: Color.h,v $
///		Revision 1.4  2012/01/21 17:36:56  thomas
///		Checkpoint 3, working baseline.
///
///		Revision 1.3  2011/12/28 19:54:02  thomas
///		Checkpoint 2, genericized shape handling.
///
///		Revision 1.2  2011/12/28 18:47:49  thomas
///		Checkpoint 2, functioning baseline.
///
///		Revision 1.1  2011/12/23 19:21:37  thomas
///		Initial revision
///
///
///

#ifndef COLOR_H
#define COLOR_H

#include <iostream>
using namespace std;

#include <ijsonserializable.h>

namespace Raytracer_n {

class Color : public IJsonSerializable
{

    friend ostream& operator<<(ostream& os, const Color& other);

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
    ~Color();

    Json::Value serialize() const;

    ///
    /// @name R
    ///
    /// @description
    /// 	Accessor for the _r member variable.
    ///
    /// @return - the red component of this color
    ///
    float R() const;

    ///
    /// @name G
    ///
    /// @description
    /// 	Accessor for the _g member variable.
    ///
    /// @return - the green component of this color
    ///
    float G() const;

    ///
    /// @name B
    ///
    /// @description
    /// 	Accessor for the _b member variable.
    ///
    /// @return - the blue component of this color
    ///
    float B() const;

    inline void Clamp();

    Color& operator=(const Color& other);

    inline Color operator*(const Color& other);

    inline Color operator*(float scalar);

    inline Color& operator*=(float scalar);

    inline Color operator/(float scalar);

    inline Color& operator/=(float scalar);

    inline Color operator+(const Color& other);

    inline Color& operator+=(const Color& other);

    const static Color BLACK;

private:

    ///
    /// @name _r
    ///
    /// @description
    ///		The red component of this color.
    ///
    float _r;

    ///
    /// @name _g
    ///
    /// @description
    ///		The green component of this color.
    ///
    float _g;

    ///
    /// @name _b
    ///
    /// @description
    ///		The blue component of this color.
    ///
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
inline void Color::Clamp() {
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

}   // namespace Raytracer_n

#endif



