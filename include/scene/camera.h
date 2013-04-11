/*
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 */

#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include "point.h"
#include "vector.h"
#include "ijsonserializable.h"

namespace RadRt
{

class Camera : IJsonSerializable
{
public:

    Camera();

    Point location() const { return m_location; };
    Vector view_vector() const { return m_view_vector; };
    Vector up_vector() const { return m_up_vector; };

    void set_location(const Point &location)
    {
    	this->m_location = location;
    };

    void set_view_vector(const Vector &view_vector)
    {
    	this->m_view_vector = view_vector;
    };

    void set_up_vector(const Vector &up_vector)
    {
    	this->m_up_vector = up_vector;
    };

    Json::Value serialize() const;
    void deserialize(const Json::Value &root);

private:

    Point m_location;

    float m_focal_length;

    Vector m_view_vector;
    Vector m_up_vector;
};

}   // namespace RadRt

#endif // CAMERA_H_INCLUDED
