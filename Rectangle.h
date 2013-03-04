///
/// @file Rectangle.h
///
/// @author	Thomas Kohlman
/// @date 27 December 2011
///
/// @description
/// 	Declares a rectangle from the Shape base class.
///

#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Shape.h"

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

    Rectangle() {};

    ///
    /// @name ~Rectangle
    ///
    /// @description
    /// 	Destructor
    ///
    ~Rectangle( void );

    void init();

    void serialize(ostream &os);

    Json::Value serialize() const;
    void deserialize(const Json::Value &root);

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

    const Point &getA() const;
    const Point &getB() const;
    const Point &getC() const;
    const Point &getD() const;

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

};  // class Rectangle


inline const Point &Rectangle::getA() const
{
    return _a;
}

inline const Point &Rectangle::getB() const
{
    return _b;
}

inline const Point &Rectangle::getC() const
{
    return _c;
}

inline const Point &Rectangle::getD() const
{
    return _d;
}

}   // namespace Raytracer_n

#endif


