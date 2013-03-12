/*
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 */

#ifndef SHAPE_H
#define SHAPE_H

#include "point.h"
#include "color.h"
#include "vector.h"
#include "proceduralshader.h"
#include "ijsonserializable.h"

namespace RadRt
{

class Ray;

class Shape : public IJsonSerializable
{
public:

    Shape() : shader(nullptr) {};

    ///
    /// @name ~Shape
    ///
    /// @description
    /// 	Destructor
    ///
    ~Shape();

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
    virtual Color getAmbientColor(Point p);

    ///
    /// @name GetDiffuseColor
    ///
    /// @description
    /// 	Accessor for diffuse light component of this object.
    ///
    /// @param - point on surface for color calculation
    /// @return - the diffuse light component of this object
    ///
    virtual Color getDiffuseColor(Point p);

    ///
    /// @name GetSpecularColor
    ///
    /// @description
    /// 	Accessor for specular light component of this object.
    ///
    /// @return - the specular light component of this object
    ///
    Color getSpecularColor() const { return mSpecularColor; };

    float getAmbientConstant() const { return mAmbientConstant; };
    float getDiffuseConstant() const { return mDiffuseConstant; };
    float getSpecularConstant() const { return mSpecularConstant; };
    int getSpecularExponent() const { return mSpecularExponent; };
    float getReflectiveConstant() const { return mReflectionValue; };
    float getTransmissiveConstant() const { return mTransmissionValue; };
    float getRefractionIndex() const { return mRefractionIndex; };

    virtual Ray *intersect(const Ray &ray) = 0;

    void setProceduralShader( ProceduralShader *newShader );

private:

    ///
    /// @name mAmbientColor
    ///
    /// @description
    ///		Ambient light component for this object.
    ///
    Color mAmbientColor;

    ///
    /// @name mDiffuseColor
    ///
    /// @description
    ///		Diffuse light component for this object.
    ///
    Color mDiffuseColor;

    ///
    /// @name mSpecularColor
    ///
    /// @description
    ///		Specular light component for this object.
    ///
    Color mSpecularColor;

    ///
    /// @name mAmbientConstant
    ///
    /// @description
    ///		Ambient contribution to local illumination.
    ///
    float mAmbientConstant;

    ///
    /// @name mDiffuseExponent
    ///
    /// @description
    ///		Diffuse contribution to local illumination.
    ///
    float mDiffuseConstant;

    ///
    /// @name mSpecularExponent
    ///
    /// @description
    ///		Specular contribution to local illumination.
    ///
    float mSpecularConstant;

    ///
    /// @name mSpecularExponent
    ///
    /// @description
    ///		Property that controls the size of specular highlight.
    ///
    int mSpecularExponent;

    ///
    /// @name mReflectionConstant
    ///
    /// @description
    ///		Reflection constant of this object.
    ///
    float mReflectionValue;

    ///
    /// @name mTransmissionConstant
    ///
    /// @description
    ///		Transmission constant of this object.
    ///
    float mTransmissionValue;

    ///
    /// @name mRefractionIndex
    ///
    /// @description
    ///		Index of refraction of this object.
    ///
    float mRefractionIndex;

    ProceduralShader *shader;

};  // class Shape

//
// GetAmbientColor
//
inline Color Shape::getAmbientColor(Point p)
{
    if (shader == nullptr)
        return mAmbientColor;
    else
        return shader->shade(p);
}

//
// GetDiffuseColor
//
inline Color Shape::getDiffuseColor(Point p)
{
    if (shader == nullptr)
        return mDiffuseColor;
    else
        return shader->shade(p);
}

inline void Shape::setProceduralShader( ProceduralShader *newShader )
{
    if (shader != nullptr)
    {
        delete shader;
    }

    shader = newShader;
}

}   // namespace RadRt

#endif



