/*
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 */

#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>
#include <iostream>

#include "ijsonserializable.h"

namespace RadRt
{

class Vector : public IJsonSerializable
{

    friend inline Vector vector_add(const Vector &a, const Vector &b)
    {
        return Vector(a.m_x_component + b.m_x_component,
        		      a.m_y_component + b.m_y_component,
        		      a.m_z_component + b.m_z_component);
    }

    friend inline Vector normalize(const Vector &v)
    {
        double s = 1.0 / length(v);
        return Vector(v.m_x_component * s,
        		      v.m_y_component * s,
        		      v.m_z_component * s);
    }

    friend inline float length(const Vector &v)
    {
        return (float) sqrt(v.m_x_component * v.m_x_component +
        		            v.m_y_component * v.m_y_component +
        		            v.m_z_component * v.m_z_component);
    }

    friend inline Vector scalar_multiply(const Vector &v, const float scalar)
    {
        return Vector(v.m_x_component * scalar,
        			  v.m_y_component * scalar,
        			  v.m_z_component * scalar);
    }

    friend inline float dot_product(const Vector &v1, const Vector &v2)
    {
        return ((v1.m_x_component * v2.m_x_component) +
                (v1.m_y_component * v2.m_y_component) +
                (v1.m_z_component * v2.m_z_component));
    }

    friend inline Vector cross_product(const Vector &v1, const Vector &v2)
    {
        return Vector(v1.m_y_component * v2.m_z_component -
        		      v1.m_z_component * v2.m_y_component,
                      v1.m_z_component * v2.m_x_component -
                      v1.m_x_component * v2.m_z_component,
                      v1.m_x_component * v2.m_y_component -
                      v1.m_y_component * v2.m_x_component);
    }

    friend inline Vector vector_subtract(const Vector &v1, const Vector &v2)
    {
        return Vector(v1.m_x_component - v2.m_x_component, v1.m_y_component - v2.m_y_component, v1.m_z_component - v2.m_z_component);
    }

    friend inline Vector negate_vector(const Vector &v)
    {
        return Vector(-v.m_x_component, -v.m_y_component, -v.m_z_component);
    }

public:

    ///
    /// @name Vector
    ///
    /// @description
    /// 	Constructor
    ///
    /// @param x - x-axis component of this vector
    /// @param y - y-axis component of this vector
    /// @param z - z-axis component of this vector
    ///
    Vector(float x, float y, float z);

    ///
    /// @name Vector
    ///
    /// @description
    /// 	Default constructor
    ///
    Vector();

    ///
    /// @name ~Vector
    ///
    /// @description
    /// 	Destructor
    ///
    ~Vector() {};

    Json::Value serialize() const;
    void deserialize(const Json::Value &root);

    inline float x_component() const { return m_x_component; };
    inline float y_component() const { return m_y_component; };
    inline float z_component() const { return m_z_component; };

private:

    float m_x_component;
    float m_y_component;
    float m_z_component;

};  // class Vector

}   // namespace RadRt

#endif
