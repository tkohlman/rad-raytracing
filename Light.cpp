///
/// @file Light.cpp
///
/// @author	Thomas Kohlman
/// @date 19 January 2012
///
/// @description
/// 	A point light source in a 3D scene.
///

#include "Light.h"
using namespace Raytracer_n;

//
// Constructor
//
Light::Light(Point position, Color color) :
    mPosition(position), mColor(color) {
}

//
// Destructor
//
Light::~Light() { }

//
// GetPosition
//
Point Light::GetPosition() {
    return mPosition;
}

//
// GetColor
//
Color Light::GetColor() {
    return mColor;
}

Json::Value Light::serialize() const
{
    Json::Value root;
    root["position"] = mPosition.serialize();
    root["color"] = mColor.serialize();
    return root;
}

