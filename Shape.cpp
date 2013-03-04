///
/// @file Shape.cpp
///
/// @author	Thomas Kohlman
/// @date 27 December 2011
///
/// @description
/// 	Implements part of an abstract Shape representation.
///
/// Version:
/// 	$Id: Shape.cpp,v 1.3 2012/01/21 17:39:00 thomas Exp thomas $
///
/// Revisions:
///		$Log: Shape.cpp,v $
///		Revision 1.3  2012/01/21 17:39:00  thomas
///		Checkpoint 3, working baseline.
///
///		Revision 1.2  2011/12/28 18:47:18  thomas
///		Checkpoint 2, functioning baseline.
///
///		Revision 1.1  2011/12/27 19:10:12  thomas
///		Initial revision
///
///
///

#include "Shape.h"
using namespace Raytracer_n;

#include <proceduralshaderfactory.h>

//
// Constructor
//
Shape::Shape( Color ambientColor, Color diffuseColor, Color specularColor,
              float ambientConstant, float diffuseConstant,
              float specularConstant, float specularExponent,
              float reflectionValue, float transmissionValue,
              float refractionIndex ) :

    mAmbientColor(ambientColor), mDiffuseColor(diffuseColor),
    mSpecularColor(specularColor), mAmbientConstant(ambientConstant),
    mDiffuseConstant(diffuseConstant), mSpecularConstant(specularConstant),
    mSpecularExponent(specularExponent), mReflectionValue(reflectionValue),
    mTransmissionValue(transmissionValue), mRefractionIndex(refractionIndex)
{
    shader = NULL;
}

//
// Destructor
//
Shape::~Shape()
{
    if (shader != NULL)
    {
        delete shader;
    }
}

void Shape::serialize(std::ostream &os)
{
    os << " " << mAmbientColor.R();
    os << " " << mAmbientColor.G();
    os << " " << mAmbientColor.B();
    os << " " << mDiffuseColor.R();
    os << " " << mDiffuseColor.G();
    os << " " << mDiffuseColor.B();
    os << " " << mSpecularColor.R();
    os << " " << mSpecularColor.G();
    os << " " << mSpecularColor.B();
    os << " " << mAmbientConstant;
    os << " " << mDiffuseConstant;
    os << " " << mSpecularConstant;
    os << " " << mSpecularExponent;
    os << " " << mReflectionValue;
    os << " " << mTransmissionValue;
    os << " " << mRefractionIndex;
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

    if (shader != NULL)
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
