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
    mTransmissionValue(transmissionValue), mRefractionIndex(refractionIndex) {
    
}

//
// Destructor
//
Shape::~Shape() { }




