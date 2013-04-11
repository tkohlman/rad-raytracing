/*
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 */

#include "camera.h"

namespace RadRt
{

// Default camera is at the origin
// View vector is negative z-axis
// Up vector is positive y-axis
// Focal point is 1 unit along view vector
Camera::Camera():
    m_location(0,0,0),
    m_focal_length(6.0),
    m_view_vector(0,0,-1),
    m_up_vector(0,1,0),
    m_horizontal_spread(45)
{
}

Json::Value Camera::serialize() const
{
    Json::Value root;
    root["location"] = m_location.serialize();
    root["view_vector"] = m_view_vector.serialize();
    root["up_vector"] = m_up_vector.serialize();
    root["focal_point"] = m_focal_length;
    root["horizontal_spread"] = m_horizontal_spread;
    return root;
}

void Camera::deserialize(const Json::Value &root)
{
    m_location.deserialize(root["location"]);
    m_view_vector.deserialize(root["view_vector"]);
    m_up_vector.deserialize(root["up_vector"]);
    m_focal_length = root["focal_length"].asFloat();
    m_horizontal_spread = root["horizontal_spread"].asFloat();
}

}   // namespace RadRt
