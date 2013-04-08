/*
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 */

#ifndef LIGHT_H
#define LIGHT_H

#include "point.h"
#include "color.h"
#include "ijsonserializable.h"

namespace RadRt
{

class Light : IJsonSerializable
{
public:

    ///
    /// @name Light
    ///
    /// @description
    /// 	Constructor
    ///
    /// @param position - the position of the light source
    /// @param color - the color of the light source
    ///
    Light(Point position, Color color);

    Light() {};

    ///
    /// @name ~Light
    ///
    /// @description
    /// 	Destructor
    ///
    ~Light() {};

    Json::Value serialize() const;
    void deserialize(const Json::Value &root);

    Point getPosition() const { return mPosition; };
    Color getColor() const { return mColor; };

private:

    ///
    /// @name mPosition
    ///
    /// @description
    ///		The position of the light source.
    ///
    Point mPosition;

    ///
    /// @name mColor
    ///
    /// @description
    ///	    The color of the light source.
    ///
    Color mColor;

};  // class Light

}   // namespace RadRt

#endif
