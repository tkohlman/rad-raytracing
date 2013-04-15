/*
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 */

#ifndef SHAPE_H
#define SHAPE_H

#include "point3d.h"
#include "color.h"
#include "vector3d.h"
#include "proceduralshader.h"
#include "ijsonserializable.h"

namespace RadRt
{

class Ray;

class Shape : public IJsonSerializable
{
public:

    ///
    /// @name ~Shape
    ///
    /// @description
    /// 	Destructor
    ///
    virtual ~Shape();

    virtual Json::Value serialize() const;
    virtual void deserialize(const Json::Value &root);

    ///
    /// @name GetAmbientColor();
    ///
    /// @description
    /// 	Accessor for ambient light component of this object.
    ///
    /// @param - point on surface for color calculation
    /// @return - the ambient light component of this object
    ///
    virtual Color ambient_color(Point3d p);

    ///
    /// @name GetDiffuseColor
    ///
    /// @description
    /// 	Accessor for diffuse light component of this object.
    ///
    /// @param - point on surface for color calculation
    /// @return - the diffuse light component of this object
    ///
    virtual Color diffuse_color(Point3d p);

    ///
    /// @name GetSpecularColor
    ///
    /// @description
    /// 	Accessor for specular light component of this object.
    ///
    /// @return - the specular light component of this object
    ///
    Color specular_color() const { return m_specular_color; };

    float ambient_constant() const { return m_ambient_constant; };
    float diffuse_constant() const { return m_diffuse_constant; };
    float specular_constant() const { return m_specular_constant; };
    int specular_exponent() const { return m_specular_exponent; };
    float reflective_constant() const { return m_reflection_constant; };
    float transmissive_constant() const { return m_transmission_constant; };
    float refraction_index() const { return m_refraction_index; };

    virtual Ray *intersect(const Ray &ray) = 0;

    void set_shader( ProceduralShader *newShader );

private:

    Color m_ambient_color;
    Color m_diffuse_color;
    Color m_specular_color;
    float m_ambient_constant;
    float m_diffuse_constant;
    float m_specular_constant;
    int m_specular_exponent;
    float m_reflection_constant;
    float m_transmission_constant;
    float m_refraction_index;

    ProceduralShader *m_shader;

};  // class Shape

inline Color Shape::ambient_color(Point3d p)
{
    if (m_shader == nullptr)
        return m_ambient_color;
    else
        return m_shader->shade(p);
}

inline Color Shape::diffuse_color(Point3d p)
{
    if (m_shader == nullptr)
        return m_diffuse_color;
    else
        return m_shader->shade(p);
}

inline void Shape::set_shader( ProceduralShader *shader )
{
    if (m_shader != nullptr)
    {
        delete m_shader;
    }

    m_shader = shader;
}

}   // namespace RadRt

#endif
