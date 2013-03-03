///
/// @file Light.h
///
/// @author	Thomas Kohlman
/// @date 19 January 2012
///
/// @description
/// 	A point light source in a 3D scene.
///

#ifndef LIGHT_H
#define LIGHT_H

#include "Point.h"
#include "Color.h"

#include <ijsonserializable.h>

namespace Raytracer_n {

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
    /// @return - void
    ///
    Light(Point position, Color color);

    ///
    /// @name ~Light
    ///
    /// @description
    /// 	Destructor
    ///
    /// @return - void
    ///
    ~Light();

    Json::Value serialize() const;

    ///
    /// @name GetPosition
    ///
    /// @description
    /// 	Accessor for the light's position.
    ///
    /// @return - the position of the light
    ///
    Point GetPosition();

    ///
    /// @name GetColor
    ///
    /// @description
    /// 	Accessor for the light's color.
    ///
    /// @return - the color of the light
    ///
    Color GetColor();

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

}   // namespace Raytracer_n

#endif



