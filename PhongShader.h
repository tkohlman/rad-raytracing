///
/// @file PhongShader.h
/// 
/// @author	Thomas Kohlman
/// @date 3 February 2012
///
/// @description
/// 	Implements a Phong shading model.
///
/// Version:
/// 	$Id$
/// 
/// Revisions:
///		$Log$
///
///

#ifndef PHONG_SHADER_H
#define PHONG_SHADER_H

#include "Color.h"
#include "Light.h"
#include "Shape.h"
#include "Point.h"
#include "World.h"

#include <vector>
using namespace std;

namespace Raytracer_n {

class PhongShader {

public:

    ///
    /// @name PhongShader
    /// 
    /// @description
    /// 	Constructor
    ///
    /// @param lights - the lights in the scene
    /// @param shapes - the shapes in the scene
    /// @param world - the world
    ///
    PhongShader(vector<Light> lights, vector<Shape*> shapes, World world);

    ///
    /// @name ~PhongShader
    /// 
    /// @description
    /// 	Destructor
    ///
    ~PhongShader();

    ///
    /// @name Shade
    /// 
    /// @description
    /// 	Performs a Phong shade.
    ///
    /// @param object - the shape to shade
    /// @param intersection - the point on the shapes surface we are shading
    /// @param camera - the position of the camera
    ///
    /// @return - the color of the point
    ///
    Color Shade(Shape *object, Point intersection, Point camera);

private:

    ///
    /// @name mShapes
    /// 
    /// @description
    /// 	Vector of shapes in the scene.
    ///
    vector<Shape*> mShapes;
   
    ///
    /// @name mLights
    /// 
    /// @description
    /// 	Vector of lights in the scene.
    /// 
    vector<Light> mLights;

    ///
    /// @name mWorld
    /// 
    /// @description
    /// 	Object with world constants.
    ///    
    World mWorld;

};  // class PhongShader

}   // namespace Raytracer_n

#endif




