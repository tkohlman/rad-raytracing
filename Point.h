///
/// @file Point.h
/// 
/// @author	Thomas Kohlman
/// @date 23 December 2011
///
/// @description
/// 	Declares a 3D point representation.
///
/// Version:
/// 	$Id: Point.h,v 1.4 2012/01/21 17:39:00 thomas Exp thomas $
/// 
/// Revisions:
///		$Log: Point.h,v $
///		Revision 1.4  2012/01/21 17:39:00  thomas
///		Checkpoint 3, working baseline.
///
///		Revision 1.3  2011/12/28 19:54:02  thomas
///		Checkpoint 2, genericized shape handling.
///
///		Revision 1.2  2011/12/28 18:47:49  thomas
///		Checkpoint 2, functioning baseline.
///
///		Revision 1.1  2011/12/23 19:35:13  thomas
///		Initial revision
///
///
///

#ifndef POINT_H
#define POINT_H

#include "Vector.h"
#include "Color.h"

namespace Raytracer_n {

class Point {

    friend ostream& operator<<(ostream& os, const Point& point);

public:

    ///
    /// @name Point
    /// 
    /// @description
    /// 	Constructor
    ///
    /// @param x - x-axis component of constructed point
    /// @param y - y-axis component of constructed point
    /// @param z - z-axis component of constructed point
    /// @param c - the color of the point
    /// @return - void
    ///
    Point(float x, float y, float z, Color c);
    
    Point(float x, float y, float z);

    ///
    /// @name Point
    /// 
    /// @description
    /// 	Constructor
    ///
    /// @param p - starting point
    /// @param v - direction vector
    /// @param distance - distance along direction vector
    /// @return - void
    ///
    Point(const Point& p, const Vector& v, const float& distance);

    ///
    /// @name Point
    /// 
    /// @description
    /// 	Copy Constructor
    ///
    /// @param other - Point object to copy
    /// @return - void
    ///
    Point(const Point& other);
    
    ///
    /// @name Point
    /// 
    /// @description
    /// 	Default Constructor
    ///
    /// @return - void
    ///
    Point();

    ///
    /// @name ~Point
    /// 
    /// @description
    /// 	Destructor
    ///
    /// @return - void
    ///
    ~Point();

    ///
    /// @name X
    /// 
    /// @description
    /// 	Accessor for _x member variable.
    ///
    /// @return - x-axis component of this point
    ///    
    float X() const;

    ///
    /// @name Y
    /// 
    /// @description
    /// 	Accessor for _y member variable.
    ///
    /// @return - y-axis component of this point
    ///    
    float Y() const;

    ///
    /// @name Z
    /// 
    /// @description
    /// 	Accessor for _z member variable.
    ///
    /// @return - z-axis component of this point
    ///    
    float Z() const;
    
    ///
    /// @name GetColor
    ///
    /// @description
    ///     Accessor for the _color member variable.
    ///
    /// @return - the color of this point
    ///
    Color GetColor() const;
    
    ///
    /// @name operator-
    /// 
    /// @description
    /// 	Calculates a vector defined by two endpoints.
    ///
    /// @param other - the second point
    /// @return - 
    ///
    Vector operator-(const Point& other);
    
    ///
    /// @name operator=
    /// 
    /// @description
    /// 	Equals assignment operator.
    ///
    /// @param other - the second point
    /// @return - address of this argument
    ///
    Point& operator=(const Point& other);
    
    ///
    /// @name distance
    ///
    /// @description
    ///     Calculates distance between two points.
    ///
    /// @param other - second point in distance calculation
    /// @return - the distance between this point and the other point
    ///
    inline float distance(const Point& other) const;

private:

    ///
    /// @name _x
    ///
    /// @description
    ///		The x-axis component of this point.
    ///
    float _x;
    
    ///
    /// @name _y
    ///
    /// @description
    ///		The y-axis component of this point.
    ///    
    float _y;
    
    ///
    /// @name _z
    ///
    /// @description
    ///		The z-axis component of this point.
    ///    
    float _z;
    
    ///
    /// @name _color
    ///
    /// @description
    ///     The color of this point.
    ///
    Color _color;


};  // class Point

//
// distance
//
inline float Point::distance(const Point& other) const {

    float dx = _x - other.X();
    float dy = _y - other.Y();
    float dz = _z - other.Z();
    
    return sqrt((dx*dx) + (dy*dy) + (dz*dz));

}

}   // namespace Raytracer_n

#endif

