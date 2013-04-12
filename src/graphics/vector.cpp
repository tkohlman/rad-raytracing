/*
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 */

#include "vector.h"

namespace RadRt
{

Vector3d::Vector3d(float x, float y, float z):
    m_x_component(x),
    m_y_component(y),
    m_z_component(z)
{
}

Vector3d::Vector3d():
    m_x_component(0),
    m_y_component(0),
    m_z_component(0)
{
}

Json::Value Vector3d::serialize() const
{
    Json::Value root;
    root["x"] = m_x_component;
    root["y"] = m_y_component;
    root["z"] = m_z_component;
    return root;
}

void Vector3d::deserialize(const Json::Value &root)
{
    m_x_component = root["x"].asFloat();
    m_y_component = root["y"].asFloat();
    m_z_component = root["z"].asFloat();
}

}   // namespace RadRt
