/*
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 */

#include "light.h"

namespace RadRt
{

Light::Light(Point position, Color color):
    m_position(position),
    m_color(color)
{
}

Json::Value Light::serialize() const
{
    Json::Value root;
    root["position"] = m_position.serialize();
    root["color"] = m_color.serialize();
    return root;
}

void Light::deserialize(const Json::Value &root)
{
    m_position.deserialize(root["position"]);
    m_color.deserialize(root["color"]);
}

}   // namespace RadRt
