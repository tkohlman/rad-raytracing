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

    Point getLocation() const { return location; };
    Vector getView() const { return view; };

    void setLocation(const Point &location) { this->location = location; };
    void setView(const Vector &view) { this->view = view; };

    Json::Value serialize() const;
    void deserialize(const Json::Value &root);

private:

    Point location;
    Vector view;

};

}   // namespace RadRt

#endif // CAMERA_H_INCLUDED