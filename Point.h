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

#include <ijsonserializable.h>

namespace Raytracer_n {

class Point {

    friend ostream& operator<<(ostream &os, const Point &point)
    {
        os << "(" << point._x << ", " << point._y << ", " << point._z << ")";
        return os;
    }

    friend inline float distanceBetween( const Point &p1, const Point &p2 )
    {
        float dx = p1._x - p2._x;
        float dy = p1._y - p2._y;
        float dz = p1._z - p2._z;

        return sqrt((dx*dx) + (dy*dy) + (dz*dz));
    }

    friend inline Vector displacementVector( const Point &p1, const Point &p2 )
    {
        return Vector(p1._x - p2._x, p1._y - p2._y, p1._z - p2._z);
    }


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
    /// @return - void
    ///
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

    Json::Value serialize() const;
    void deserialize(const Json::Value &root);

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

};  // class Point



}   // namespace Raytracer_n

#endif

