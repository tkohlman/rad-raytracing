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
    ///
    Color(float red, float green, float blue);

    ///
    /// @name Color
    ///
    /// @description
    /// 	Copy constructor
    ///
    /// @param other - Color object to copy
    ///
    Color(const Color& other);

    ///
    /// @name Color
    ///
    /// @description
    /// 	Default constructor
    ///
    Color();

    ///
    /// @name ~Color
    ///
    /// @description
    /// 	Destructor
    ///
    ~Color() {};

    Json::Value serialize() const;
    void deserialize(const Json::Value &root);

    float red() const { return m_red; };
    float green() const { return m_green; };
    float blue() const { return m_blue; };

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
    float m_red;
    float m_green;
    float m_blue;

};  // class Color

inline Color Color::operator*(const Color& other)
{
    return Color(m_red   * other.m_red,
    			 m_green * other.m_green,
    			 m_blue  * other.m_blue);
}

inline Color Color::operator*(float scalar)
{
    return Color(m_red * scalar, m_green * scalar, m_blue * scalar);
}

inline Color& Color::operator*=(float scalar)
{
    m_red *= scalar;
    m_green *= scalar;
    m_blue *= scalar;
    return *this;
}

inline Color Color::operator/(float scalar)
{
    if (scalar != 0)
        return Color(m_red / scalar, m_green / scalar, m_blue / scalar);
    else
        return Color(m_red, m_green, m_blue);
}

inline Color& Color::operator/=(float scalar)
{
    if (scalar != 0)
    {
        m_red /= scalar;
        m_green /= scalar;
        m_blue /= scalar;
    }
    return *this;
}

inline Color Color::operator+(const Color& other)
{
    return Color(m_red   + other.m_red,
    			 m_green + other.m_green,
    			 m_blue  + other.m_blue);
}

inline Color& Color::operator+=(const Color& other)
{
    m_red += other.m_red;
    m_green += other.m_green;
    m_blue += other.m_blue;
    return *this;
}

inline void Color::clamp()
{
    if (m_red > 1.0)
    {
        m_red = 1.0;
    }
    if (m_green > 1.0)
    {
        m_green = 1.0;
    }
    if (m_blue > 1.0)
    {
        m_blue = 1.0;
    }
}

}   // namespace RadRt

#endif
