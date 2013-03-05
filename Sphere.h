///
/// @file Sphere.h
///
/// @author	Thomas Kohlman
/// @date 28 December 2011
///
/// @description
/// 	Declares a sphere from the shape base class.
///
/// Version:
/// 	$Id: Sphere.h,v 1.5 2012/01/21 17:39:00 thomas Exp thomas $
///
/// Revisions:
///		$Log: Sphere.h,v $
///		Revision 1.5  2012/01/21 17:39:00  thomas
///		Checkpoint 3, working baseline.
///
///		Revision 1.4  2011/12/29 02:25:36  thomas
///		Removed unnecessary dynamic memory.
///
///		Revision 1.3  2011/12/28 19:54:02  thomas
///		Checkpoint 2, genericized shape handling.
///
///		Revision 1.2  2011/12/28 18:47:49  thomas
///		Checkpoint 2, functioning baseline.
///
///		Revision 1.1  2011/12/28 16:41:45  thomas
///		Initial revision
///
///
///

#ifndef SPHERE_H
#define SPHERE_H

#include "Shape.h"

namespace Raytracer_n {

class Sphere : public Shape {

public:

    ///
    /// @name Sphere
    ///
    /// @description
    /// 	Constructor
    ///
    /// @param center - the center point of the sphere
    /// @param radius - the radius of the sphere
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
    Sphere( Point center, float radius,
            Color ambientColor, Color diffuseColor, Color specularColor,
            float ambientConstant, float diffuseConstant,
            float specularConstant, float specularExponent,
            float reflectionValue, float transmissionValue,
            float refractionIndex );

    Sphere() {};
    ~Sphere() {};

    Json::Value serialize() const;
    void deserialize(const Json::Value &root);

    ///
    /// @name Intersect
    ///
    /// @description
    /// 	Determines if a ray intersects the sphere.
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
    /// 	Calculates the surface normal for a point on the sphere's surface.
    ///
    /// @param surface - a point on the sphere's surface
    /// @return - the surface normal at this point on the sphere
    ///
    Vector GetSurfaceNormal(Point surface);

private:

    ///
    /// @name _center
    ///
    /// @description
    ///		The center point of the sphere.
    ///
    Point _center;

    ///
    /// @name _radius
    ///
    /// @description
    ///		The radius of the sphere.
    ///
    float _radius;



};  // class Sphere

}   // namespace Raytracer_n

#endif



