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
    Light(Point3d position, Color color);

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

    Point3d getPosition() const { return m_position; };
    Color getColor() const { return m_color; };

private:


    Point3d m_position;

    Color m_color;

};  // class Light

}   // namespace RadRt

#endif
