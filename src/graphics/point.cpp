/*
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 */

#include "point.h"

namespace RadRt
{

Point::Point(float x, float y, float z):
    m_x_coord(x),
    m_y_coord(y),
    m_z_coord(z)
{
}

Point::Point(const Point& other):
    m_x_coord(other.m_x_coord),
    m_y_coord(other.m_y_coord),
    m_z_coord(other.m_z_coord)
{
}

Point::Point(const Point& p, const Vector& v, const float& distance)
{
    m_x_coord = p.m_x_coord + v.x_component() * distance;
    m_y_coord = p.m_y_coord + v.y_component() * distance;
    m_z_coord = p.m_z_coord + v.z_component() * distance;
}

Point::Point()
{
    m_x_coord = m_y_coord = m_z_coord = 0;
}

Json::Value Point::serialize() const
{
    Json::Value root;
    root["x"] = m_x_coord;
    root["y"] = m_y_coord;
    root["z"] = m_z_coord;
    return root;
}

void Point::deserialize(const Json::Value &root)
{
    m_x_coord = root["x"].asFloat();
    m_y_coord = root["y"].asFloat();
    m_z_coord = root["z"].asFloat();
}

}   // namespace RadRt
