///
/// @file Light.cpp
/// 
/// @author	Thomas Kohlman
/// @date 19 January 2012
///
/// @description
/// 	A point light source in a 3D scene.
///
/// Version:
/// 	$Id: Light.cpp,v 1.2 2012/01/21 17:37:58 thomas Exp thomas $
/// 
/// Revisions:
///		$Log: Light.cpp,v $
///		Revision 1.2  2012/01/21 17:37:58  thomas
///		Checkpoint 3, working baseline.
///
///		Revision 1.1  2012/01/20 03:17:26  thomas
///		Initial revision
///
///
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



