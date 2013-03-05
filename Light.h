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

#include <Point.h>
#include <Color.h>
#include <ijsonserializable.h>

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
    /// @return - void
    ///
    Light(Point position, Color color);

    Light() {};

    ///
    /// @name ~Light
    ///
    /// @description
    /// 	Destructor
    ///
    /// @return - void
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



