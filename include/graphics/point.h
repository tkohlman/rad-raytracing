/*
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 */

#ifndef POINT_H
#define POINT_H

#include "vector.h"
#include "color.h"

#include <ijsonserializable.h>

namespace RadRt
{

class Point
{
    friend inline float distance_between(const Point &p1, const Point &p2)
    {
        float dx = p1.m_x_coord - p2.m_x_coord;
        float dy = p1.m_y_coord - p2.m_y_coord;
        float dz = p1.m_z_coord - p2.m_z_coord;

        return sqrt((dx*dx) + (dy*dy) + (dz*dz));
    }

    friend inline Vector displacement_vector(const Point &p1, const Point &p2)
    {
        return Vector(p1.m_x_coord - p2.m_x_coord,
        		      p1.m_y_coord - p2.m_y_coord,
        		      p1.m_z_coord - p2.m_z_coord);
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
    ///
    Point(const Point& p, const Vector& v, const float& distance);

    ///
    /// @name Point
    ///
    /// @description
    /// 	Copy Constructor
    ///
    /// @param other - Point object to copy
    ///
    Point(const Point& other);

    ///
    /// @name Point
    ///
    /// @description
    /// 	Default Constructor
    ///
    Point();

    ~Point() {};

    float x_coord() const { return m_x_coord; };
    float y_coord() const { return m_y_coord; };
    float z_coord() const { return m_z_coord; };

    Json::Value serialize() const;
    void deserialize(const Json::Value &root);

private:

    float m_x_coord;
    float m_y_coord;
    float m_z_coord;

};  // class Point

}   // namespace RadRt

#endif
