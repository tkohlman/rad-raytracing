/*
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 */

#include "light.h"

namespace RadRt
{

Light::Light(Point position, Color color):
    mPosition(position),
    mColor(color)
{
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
