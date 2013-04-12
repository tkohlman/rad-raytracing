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

class Vector3d : public IJsonSerializable
{

    friend inline Vector3d vector_add(const Vector3d &a, const Vector3d &b)
    {
        return Vector3d(a.m_x_component + b.m_x_component,
        		      a.m_y_component + b.m_y_component,
        		      a.m_z_component + b.m_z_component);
    }

    friend inline Vector3d normalize(const Vector3d &v)
    {
        double s = 1.0 / length(v);
        return Vector3d(v.m_x_component * s,
        		      v.m_y_component * s,
        		      v.m_z_component * s);
    }

    friend inline float length(const Vector3d &v)
    {
        return (float) sqrt(v.m_x_component * v.m_x_component +
        		            v.m_y_component * v.m_y_component +
        		            v.m_z_component * v.m_z_component);
    }

    friend inline Vector3d scalar_multiply(const Vector3d &v, const float scalar)
    {
        return Vector3d(v.m_x_component * scalar,
        			  v.m_y_component * scalar,
        			  v.m_z_component * scalar);
    }

    friend inline float dot_product(const Vector3d &v1, const Vector3d &v2)
    {
        return ((v1.m_x_component * v2.m_x_component) +
                (v1.m_y_component * v2.m_y_component) +
                (v1.m_z_component * v2.m_z_component));
    }

    friend inline Vector3d cross_product(const Vector3d &v1, const Vector3d &v2)
    {
        return Vector3d(v1.m_y_component * v2.m_z_component -
        		      v1.m_z_component * v2.m_y_component,
                      v1.m_z_component * v2.m_x_component -
                      v1.m_x_component * v2.m_z_component,
                      v1.m_x_component * v2.m_y_component -
                      v1.m_y_component * v2.m_x_component);
    }

    friend inline Vector3d vector_subtract(const Vector3d &v1, const Vector3d &v2)
    {
        return Vector3d(v1.m_x_component - v2.m_x_component, v1.m_y_component - v2.m_y_component, v1.m_z_component - v2.m_z_component);
    }

    friend inline Vector3d negate_vector(const Vector3d &v)
    {
        return Vector3d(-v.m_x_component, -v.m_y_component, -v.m_z_component);
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
    Vector3d(float x, float y, float z);

    ///
    /// @name Vector
    ///
    /// @description
    /// 	Default constructor
    ///
    Vector3d();

    ///
    /// @name ~Vector
    ///
    /// @description
    /// 	Destructor
    ///
    ~Vector3d() {};

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
