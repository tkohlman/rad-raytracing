#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include <Point.h>
#include <Vector.h>
using namespace Raytracer_n;

#include <ijsonserializable.h>

class Camera : IJsonSerializable
{
public:

    Camera();

    Point getLocation() const;
    Vector getView() const;

    void setLocation(const Point &location);
    void setView(const Vector &view);

    Json::Value serialize() const;
    void deserialize(const Json::Value &root);

private:

    Point location;
    Vector view;

};

inline Point Camera::getLocation() const
{
    return location;
}

inline Vector Camera::getView() const
{
    return view;
}

inline void Camera::setLocation(const Point &location)
{
    this->location = location;
}

inline void Camera::setView(const Vector &view)
{
    this->view = view;
}

#endif // CAMERA_H_INCLUDED
