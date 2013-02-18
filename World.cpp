///
/// @file World.cpp
/// 
/// @author	Thomas Kohlman
/// @date 19 January 2012
///
/// @description
/// 	Defines the world of a 3D scene.
///
/// Version:
/// 	$Id: World.cpp,v 1.2 2012/01/21 17:39:00 thomas Exp thomas $
/// 
/// Revisions:
///		$Log: World.cpp,v $
///		Revision 1.2  2012/01/21 17:39:00  thomas
///		Checkpoint 3, working baseline.
///
///		Revision 1.1  2012/01/20 03:07:23  thomas
///		Initial revision
///
///
///

#include "World.h"
using namespace Raytracer_n;

//
// Constructor
//
World::World(Color ka) :
    mKa(ka) {
}

//
// Destructor
//
World::~World() { }

//
// GetAmbientLight
//
Color World::GetAmbientLight() {
    return mKa;
}






