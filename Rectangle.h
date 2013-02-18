///
/// @file Rectangle.h
/// 
/// @author	Thomas Kohlman
/// @date 27 December 2011
///
/// @description
/// 	Declares a rectangle from the Shape base class.
///
/// Version:
/// 	$Id: Rectangle.h,v 1.4 2012/01/21 17:39:00 thomas Exp thomas $
/// 
/// Revisions:
///		$Log: Rectangle.h,v $
///		Revision 1.4  2012/01/21 17:39:00  thomas
///		Checkpoint 3, working baseline.
///
///		Revision 1.3  2011/12/29 02:25:36  thomas
///		Removed unnecessary dynamic memory.
///
///		Revision 1.2  2011/12/28 18:47:49  thomas
///		Checkpoint 2, functioning baseline.
///
///		Revision 1.1  2011/12/27 18:42:08  thomas
///		Initial revision
///
///
///

#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Shape.h"
#include "Color.h"
#include "Point.h"
#include "Vector.h"

namespace Raytracer_n {

class Rectangle : public Shape {

public:
    
    ///
    /// @name Rectangle
    /// 
    /// @description
    /// 	Constructor
    ///
    /// @param a - first point in rectangle
    /// @param b - second point in rectangle
    /// @param c - third point in rectangle
    /// @param d - fourth point in rectangle
    /// @param ambientColor - the ambient color of this object
    /// @param diffuseColor - the diffuse color of this object
    /// @param specularColor - the specular color of this object
    /// @param ambientConstant - contribution of ambient color
    /// @param diffuseConstant - contribution of diffuse color
    /// @param specularConstant - contribution of specular color
    /// @param specularExponent - size of specular highlight
    /// @param reflectionValue - reflectivity of this object
    /// @param transmissionValue - opacity of this object
    /// @param refractionIndex - index of reflection for this object
    ///
    Rectangle( Point a, Point b, Point c, Point d,
        Color ambientColor, Color diffuseColor, Color specularColor,
        float ambientConstant, float diffuseConstant,
        float specularConstant, float specularExponent,
        float reflectionValue, float transmissionValue,
        float refractionIndex );

    ///
    /// @name ~Rectangle
    /// 
    /// @description
    /// 	Destructor
    ///
    ~Rectangle( void );
    
    ///
    /// @name Intersect
    /// 
    /// @description
    /// 	Determines if a ray intersects the rectangle.
    ///
    /// @param v - direction vector of the ray
    /// @param o - origin of the ray
    /// @return - intersection point closest to ray origin, NULL if no
    ///           intersection occurs
    ///
    Point* Intersect(Vector v, Point o);

    ///
    /// @name GetSurfaceNormal
    /// 
    /// @description
    /// 	Calculates the surface normal for a point on the 
    ///     rectangle's surface.
    ///
    /// @param surface - a point on the rectangle's surface
    /// @return - the surface normal at this point on the rectangle
    ///
    Vector GetSurfaceNormal(Point surface);

    ///
    /// @name GetAmbientColor();
    /// 
    /// @description
    /// 	Accessor for ambient light component of this object.
    ///
    /// @param - point on surface for color calculation
    /// @return - the ambient light component of this object
    ///
    virtual Color GetAmbientColor(Point p);
   
    ///
    /// @name GetDiffuseColor
    /// 
    /// @description
    /// 	Accessor for diffuse light component of this object.
    ///
    /// @param - point on surface for color calculation
    /// @return - the diffuse light component of this object
    /// 
    virtual Color GetDiffuseColor(Point p);
   
    ///
    /// @name GetSpecularColor
    /// 
    /// @description
    /// 	Accessor for specular light component of this object.
    ///
    /// @param - point on surface for color calculation
    /// @return - the specular light component of this object
    /// 
    virtual Color GetSpecularColor(Point p);

private:

    ///
    /// @name _a
    ///
    /// @description
    ///		The first point of the rectangle.
    ///
    Point _a;
    
    
    ///
    /// @name _b
    ///
    /// @description
    ///		The second point of the rectangle.
    ///
    Point _b;
    
    ///
    /// @name _c
    ///
    /// @description
    ///		The third point of the rectangle.
    ///
    Point _c;
    
    ///
    /// @name _d
    ///
    /// @description
    ///		The fourth point of the rectangle.
    ///
    Point _d;
    
    ///
    /// @name _normal
    ///
    /// @description
    ///		The vector normal to the plane formed by the rectangle.
    ///
    Vector _normal;

    ///
    /// @name mKa
    ///
    /// @description
    ///		Ambient light component for this object.
    ///
    Color mKa;
    
    ///
    /// @name mKd
    ///
    /// @description
    ///		Diffuse light component for this object.
    ///
    Color mKd;
    
    ///
    /// @name mKs
    ///
    /// @description
    ///		Specular light component for this object.
    ///
    Color mKs;

};  // class Rectangle

}   // namespace Raytracer_n

#endif


