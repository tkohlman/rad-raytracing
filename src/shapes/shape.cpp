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
    if (shader != nullptr)
    {
        delete shader;
    }
}

Json::Value Shape::serialize() const
{
    Json::Value root;
    root["ambient_color"] = mAmbientColor.serialize();
    root["diffuse_color"] = mDiffuseColor.serialize();
    root["specular_color"] = mSpecularColor.serialize();
    root["ambient_constant"] = mAmbientConstant;
    root["diffuse_constant"] = mDiffuseConstant;
    root["specular_constant"] = mSpecularConstant;
    root["specular_exponent"] = mSpecularExponent;
    root["reflective_value"] = mReflectionValue;
    root["transmissive_value"] = mTransmissionValue;
    root["refraction_index"] = mRefractionIndex;

    if (shader != nullptr)
    {
        root["shader"] = shader->serialize();
    }
    return root;
}

void Shape::deserialize(const Json::Value &root)
{
    mAmbientColor.deserialize(root["ambient_color"]);
    mDiffuseColor.deserialize(root["diffuse_color"]);
    mSpecularColor.deserialize(root["specular_color"]);
    mAmbientConstant = root["ambient_constant"].asFloat();
    mDiffuseConstant = root["diffuse_constant"].asFloat();
    mSpecularConstant = root["specular_constant"].asFloat();
    mSpecularExponent = root["specular_exponent"].asInt();
    mReflectionValue = root["reflective_value"].asFloat();
    mTransmissionValue = root["transmissive_value"].asFloat();
    mRefractionIndex = root["refraction_index"].asFloat();

    if (root.isMember("shader"))
    {
        ProceduralShaderFactory factory;
        shader = factory.create(root["shader"]["type"].asString());
        shader->deserialize(root["shader"]);
    }
}

}   // namespace RadRt
