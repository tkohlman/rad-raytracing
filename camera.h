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

#endif // CAMERA_H_INCLUDED
