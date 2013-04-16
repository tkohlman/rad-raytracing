/**
 * @file
 * @author Thomas Kohlman
 *
 * @section LICENSE
 *
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 *
 * @section DESCRIPTION
 *
 * Represents a color with red, green, and blue components.
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

	/**
	 * Create a color from red, green, and blue components.
	 *
	 * @param red Red component of the color.
	 * @param blue Blue component of the color.
	 * @param green Green component of the color.
	 */
    Color(float red, float green, float blue);

    /**
     * Copy constructor.
     *
     * @param other Color to copy.
     */
    Color(const Color& other);

    /**
     * Create a default color object with the color black.
     */
    Color();

    /**
     * Serialize this object to JSON format.
     */
    Json::Value serialize() const;

    /**
     * Deserialize this object from JSON format.
     */
    void deserialize(const Json::Value &root);

    /**
     * Get the red component of this color.
     */
    float red() const { return m_red; };

    /**
     * Get the green component of this color.
     */
    float green() const { return m_green; };

    /**
     * Get the blue component of this color.
     */
    float blue() const { return m_blue; };

    /**
     * Reduce each color component to its maximum value if it falls outside the
     * acceptable range. For example, a blue componet value of 1.2 would be
     * reduced to 1.
     */
    inline void clamp();

    /**
     * Create a new color by multipling the componets of this color by the
     * corresponding components of a second color.
     *
     * @param other Second color to use.
     */
    inline Color operator*(const Color& other);

    /**
     * Create a new color by multipling the components of this color by a
     * scalar constant.
     *
     * @param scalar Scalar constant to use in the multiplication.
     */
    inline Color operator*(float scalar);

    /**
     * Multiply the components of this color by a scalar constant.
     *
     * @param scalar Scalar constant to use in the multiplication.
     */
    inline Color& operator*=(float scalar);

    /**
     * Create a new color by dividing the components of this color by a scalar
     * constant.
     *
     * @param scalar Scalar constant to use in the multiplication.
     */
    inline Color operator/(float scalar);

    /**
     * Divide the components of this color by a scalar constant.
     *
     * @param scalar Scalar constant to use in the division.
     */
    inline Color& operator/=(float scalar);

    /**
     * Create a new color by adding the components of this color to the
     * corresponding components of a second color.
     *
     * @param other Second color to use in the addition.
     */
    inline Color operator+(const Color& other);

    /**
     * Add the components of a second color to the corresponding components of
     * this color.
     *
     * @param other Second color to use in the addition.
     */
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
