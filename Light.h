///
/// @file Light.h
/// 
/// @author	Thomas Kohlman
/// @date 19 January 2012
///
/// @description
/// 	A point light source in a 3D scene.
///
/// Version:
/// 	$Id: Light.h,v 1.2 2012/01/21 17:38:14 thomas Exp thomas $
/// 
/// Revisions:
///		$Log: Light.h,v $
///		Revision 1.2  2012/01/21 17:38:14  thomas
///		Checkpoint 3, working baseline.
///
///		Revision 1.1  2012/01/20 03:17:09  thomas
///		Initial revision
///
///
///

#ifndef LIGHT_H
#define LIGHT_H

#include "Point.h"
#include "Color.h"

namespace Raytracer_n {

class Light {

public:

    ///
    /// @name Light
    /// 
    /// @description
    /// 	Constructor
    ///
    /// @param position - the position of the light source
    /// @param color - the color of the light source
    /// @return - void
    ///
    Light(Point position, Color color);
    
    ///
    /// @name ~Light
    /// 
    /// @description
    /// 	Destructor
    ///
    /// @return - void
    ///
    ~Light();
    
    ///
    /// @name GetPosition
    /// 
    /// @description
    /// 	Accessor for the light's position.
    ///
    /// @return - the position of the light
    ///
    Point GetPosition();
    
    ///
    /// @name GetColor
    /// 
    /// @description
    /// 	Accessor for the light's color.
    ///
    /// @return - the color of the light
    ///
    Color GetColor();

private:

    ///
    /// @name mPosition
    ///
    /// @description
    ///		The position of the light source.
    ///
    Point mPosition;
    
    ///
    /// @name mColor
    ///
    /// @description
    ///	    The color of the light source.
    ///
    Color mColor;

};  // class Light

}   // namespace Raytracer_n

#endif



