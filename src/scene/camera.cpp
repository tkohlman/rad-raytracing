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
    location(0,0,0),
    focus(1.0),
    view(0,0,-1),
    upVector(0,1,0)
{
}

Json::Value Camera::serialize() const
{
    Json::Value root;
    root["location"] = location.serialize();
    root["view"] = view.serialize();
    root["up_vector"] = upVector.serialize();
    root["focal_point"] = focus;
    return root;
}

void Camera::deserialize(const Json::Value &root)
{
    location.deserialize(root["location"]);
    view.deserialize(root["view"]);
    upVector.deserialize(root["up_vector"]);
    focus = root["focal_point"].asFloat();
}

}   // namespace RadRt
