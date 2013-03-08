///
/// @file Light.cpp
///
/// @author	Thomas Kohlman
/// @date 19 January 2012
///
/// @description
/// 	A point light source in a 3D scene.
///

#include "light.h"

namespace RadRt
{

Light::Light(Point position, Color color)
{
    mPosition = position;
    mColor = color;
}

Json::Value Light::serialize() const
{
    Json::Value root;
    root["position"] = mPosition.serialize();
    root["color"] = mColor.serialize();
    return root;
}

void Light::deserialize(const Json::Value &root)
{
    mPosition.deserialize(root["position"]);
    mColor.deserialize(root["color"]);
}

}   // namespace RadRt

