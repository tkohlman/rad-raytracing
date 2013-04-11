/*
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 */

#include "shape.h"
#include "proceduralshaderfactory.h"

namespace RadRt
{

Shape::~Shape()
{
    if (m_shader != nullptr)
    {
        delete m_shader;
    }
}

Json::Value Shape::serialize() const
{
    Json::Value root;
    root["ambient_color"] = m_ambient_color.serialize();
    root["diffuse_color"] = m_diffuse_color.serialize();
    root["specular_color"] = m_specular_color.serialize();
    root["ambient_constant"] = m_ambient_constant;
    root["diffuse_constant"] = m_diffuse_constant;
    root["specular_constant"] = m_specular_constant;
    root["specular_exponent"] = m_specular_exponent;
    root["reflective_value"] = m_reflection_constant;
    root["transmissive_value"] = m_transmission_constant;
    root["refraction_index"] = m_refraction_index;

    if (m_shader != nullptr)
    {
        root["shader"] = m_shader->serialize();
    }
    return root;
}

void Shape::deserialize(const Json::Value &root)
{
    m_ambient_color.deserialize(root["ambient_color"]);
    m_diffuse_color.deserialize(root["diffuse_color"]);
    m_specular_color.deserialize(root["specular_color"]);
    m_ambient_constant = root["ambient_constant"].asFloat();
    m_diffuse_constant = root["diffuse_constant"].asFloat();
    m_specular_constant = root["specular_constant"].asFloat();
    m_specular_exponent = root["specular_exponent"].asInt();
    m_reflection_constant = root["reflective_value"].asFloat();
    m_transmission_constant = root["transmissive_value"].asFloat();
    m_refraction_index = root["refraction_index"].asFloat();

    if (root.isMember("shader"))
    {
        ProceduralShaderFactory factory;
        m_shader = factory.create(root["shader"]["type"].asString());
        m_shader->deserialize(root["shader"]);
    }
}

}   // namespace RadRt
