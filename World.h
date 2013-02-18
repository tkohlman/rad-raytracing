///
/// @file World.h
/// 
/// @author	Thomas Kohlman
/// @date 19 January 2012
///
/// @description
/// 	Defines the world of a 3D scene.
///
/// Version:
/// 	$Id: World.h,v 1.2 2012/01/21 17:39:00 thomas Exp thomas $
/// 
/// Revisions:
///		$Log: World.h,v $
///		Revision 1.2  2012/01/21 17:39:00  thomas
///		Checkpoint 3, working baseline.
///
///		Revision 1.1  2012/01/20 03:07:43  thomas
///		Initial revision
///
///
///

#ifndef WORLD_H
#define WORLD_H

#include "Color.h"

namespace Raytracer_n {

class World {

public:

    ///
    /// @name World
    /// 
    /// @description
    /// 	Constructor
    ///
    /// @param ka - the ambient light in the world
    /// @return - void
    ///
    World(Color ka);
    
    ///
    /// @name ~World
    /// 
    /// @description
    /// 	Destructor
    ///
    /// @return - void
    ///
    ~World();
    
    ///
    /// @name GetAmbientLight
    /// 
    /// @description
    /// 	Accessor for world's ambient light.
    ///
    /// @return - the ambient light of the world.
    ///
    Color GetAmbientLight();

private:

    ///
    /// @name mKa
    ///
    /// @description
    ///		The ambient light in the world.
    ///
    Color mKa;

};  // class World

}   // namespace Raytracer_n

#endif




