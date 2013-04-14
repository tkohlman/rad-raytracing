/*
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 */

#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include "point3d.h"
#include "vector3d.h"
#include "ijsonserializable.h"

namespace RadRt
{

class Camera : IJsonSerializable
{
public:

    Camera();

    float focal_length() const { return m_focal_length; };
    Point3d location() const { return m_location; };
    Vector3d view_vector() const { return m_view_vector; };
    Vector3d up_vector() const { return m_up_vector; };

    float horizontal_spread() const { return m_horizontal_spread; };

    void set_location(const Point3d &location)
    {
    	m_location = location;
    };

    void set_view_vector(const Vector3d &view_vector)
    {
    	m_view_vector = view_vector;
    };

    void set_up_vector(const Vector3d &up_vector)
    {
    	m_up_vector = up_vector;
    };

    Json::Value serialize() const;
    void deserialize(const Json::Value &root);

private:

    void calculate_projection();

    Point3d m_location;

    float m_focal_length;

    Vector3d m_view_vector;
    Vector3d m_up_vector;

    float m_horizontal_spread;
};

}   // namespace RadRt

#endif // CAMERA_H_INCLUDED
