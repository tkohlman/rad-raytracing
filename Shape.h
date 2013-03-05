///
/// @file Shape.h
///
/// @author	Thomas Kohlman
/// @date 23 December 2011
///
/// @description
/// 	Defines an abstract shape class.
///

#ifndef SHAPE_H
#define SHAPE_H

#include "Point.h"
#include "Color.h"
#include "Vector.h"
#include "proceduralshader.h"
#include <ijsonserializable.h>

namespace RadRt
{

class Shape : public IJsonSerializable
{
public:

    ///
    /// @name Shape
    ///
    /// @description
    /// 	Constructor
    ///
    /// @param ambientColor - the ambient color of this object
    /// @param diffuseColor - the diffuse color of this object
    /// @param specularColor - the specular color of this object
    /// @param ambientConstant - contribution of ambient color
    /// @param diffuseConstant - contribution of diffuse color
    /// @param specularConstant - contribution of specular color
    /// @param specularExponent - size of specular highlight
    /// @param reflectionValue - reflectivity of this object
    /// @param transmissionValue - opacity of this object
    /// @param refractionIndex - index of reflection for this object
    ///
    Shape( Color ambientColor, Color diffuseColor, Color specularColor,
           float ambientConstant, float diffuseConstant,
           float specularConstant, float specularExponent,
           float reflectionValue, float transmissionValue,
           float refractionIndex );

    Shape() {};

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
    virtual Color GetAmbientColor(Point p);

    ///
    /// @name GetDiffuseColor
    ///
    /// @description
    /// 	Accessor for diffuse light component of this object.
    ///
    /// @param - point on surface for color calculation
    /// @return - the diffuse light component of this object
    ///
    virtual Color GetDiffuseColor(Point p);

    ///
    /// @name GetSpecularColor
    ///
    /// @description
    /// 	Accessor for specular light component of this object.
    ///
    /// @return - the specular light component of this object
    ///
    virtual Color GetSpecularColor();

    float GetAmbientConstant( void );
    float GetDiffuseConstant( void );
    float GetSpecularConstant( void );

    ///
    /// @name GetSpecularExponent
    ///
    /// @description
    /// 	Accessor for specular exponent reflectivity of this object.
    ///
    /// @return - specular exponent reflectivity of this object
    ///
    int GetSpecularExponent();

    ///
    /// @name GetReflectiveConstant
    ///
    /// @description
    /// 	Accessor to reflectivity of this object.
    ///
    /// @return - Reflectivity of this object.
    ///
    float GetReflectiveConstant();

    ///
    /// @name GetTransmissiveConstant
    ///
    /// @description
    /// 	Accessor to transmissive value of this object.
    ///
    /// @return - Transmissive value of this object.
    ///
    float GetTransmissiveConstant();

    ///
    /// @name GetRefractionIndex
    ///
    /// @description
    /// 	Accessor to refraction index of this object.
    ///
    /// @return - Refraction index of this object.
    ///
    float GetRefractionIndex();

    ///
    /// @name Intersect
    ///
    /// @description
    /// 	Determines if a ray intersects the shape.
    ///
    /// @param v - direction vector of the ray
    /// @param o - origin of the ray
    /// @return - intersection point closest to ray origin, NULL if no
    ///           intersection occurs
    ///
    virtual Point* Intersect(Vector v, Point o) = 0;

    ///
    /// @name GetSurfaceNormal
    ///
    /// @description
    /// 	Calculates the surface normal for a point on the shape's surface.
    ///
    /// @param surface - a point on the shape's surface
    /// @return - the surface normal at this point
    ///
    virtual Vector GetSurfaceNormal(Point surface) = 0;

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
// GetAmbientConstant
//
inline float Shape::GetAmbientConstant( void ) {

    return mAmbientConstant;

}

//
// GetDiffuseConstant
//
inline float Shape::GetDiffuseConstant( void ) {

    return mDiffuseConstant;

}

//
// GetSpecularConstant
//
inline float Shape::GetSpecularConstant( void )
{
    return mSpecularConstant;
}

//
// GetAmbientColor
//
inline Color Shape::GetAmbientColor(Point p)
{
    if (shader == NULL)
        return mAmbientColor;
    else
        return shader->shade(p);
}

//
// GetDiffuseColor
//
inline Color Shape::GetDiffuseColor(Point p)
{
    if (shader == NULL)
        return mDiffuseColor;
    else
        return shader->shade(p);
}

//
// GetSpecularColor
//
inline Color Shape::GetSpecularColor()
{
    return mSpecularColor;
}

//
// GetSpecularExponent
//
inline int Shape::GetSpecularExponent() {
    return mSpecularExponent;
}

//
// GetReflectiveConstant
//
inline float Shape::GetReflectiveConstant() {
    return mReflectionValue;
}

//
// GetTransmissiveConstant
//
inline float Shape::GetTransmissiveConstant() {
    return mTransmissionValue;
}

inline float Shape::GetRefractionIndex() {
    return mRefractionIndex;
}

inline void Shape::setProceduralShader( ProceduralShader *newShader )
{
    if (shader != NULL)
    {
        delete shader;
    }

    shader = newShader;
}

}   // namespace RadRt

#endif



