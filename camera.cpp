
#include <camera.h>

Camera::Camera():
    location(0,0,0), view(0,0,-1)
{
    // Default camera is at the origin, facing down the negative z-axis
}

Json::Value Camera::serialize() const
{
    Json::Value root;
    root["location"] = location.serialize();
    root["view"] = view.serialize();
    return root;
}
