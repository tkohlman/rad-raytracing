///
/// @file Raytracer.h
/// 
/// @author	Thomas Kohlman
/// @date 3 February 2012
///
/// @description
/// 	Provides raytracing functionality.
///
/// Version:
/// 	$Id$
/// 
/// Revisions:
///		$Log$
///
///

#ifndef RAYTRACER_H
#define RAYTRACER_H

#define RAY_INFINITY 1000000

#include "Color.h"
#include "PhongShader.h"
#include "Point.h"
#include "Shape.h"
#include "Vector.h"

#include <vector>
using namespace std;



namespace Raytracer_n {

class Raytracer {

public:

    ///
    /// @name Raytracer
    /// 
    /// @description
    /// 	Constructor
    ///
    /// @param maxDepth - the maximum depth for recursion
    /// @param background - background color of the scene
    /// @param shader - the shader to use for local illumination
    /// @param shapes - vector of shapes in the scene
    ///
    Raytracer(int maxDepth, Color background, PhongShader shader, 
        vector<Shape*> shapes);
 
    ///
    /// @name ~Raytracer
    /// 
    /// @description
    /// 	Destructor
    ///
    ~Raytracer();

    ///
    /// @name Trace
    /// 
    /// @description
    /// 	Performs a recursive ray trace.
    ///
    /// @param ray - the ray to trace
    /// @param origin - the origin of the ray
    /// @param depth - recursion depth
    /// @return - color of the point the ray hits
    ///    
    Color Trace(Vector ray, Point origin, int depth);

private:

    ///
    /// @name mMaxDepth
    ///
    /// @description
    ///		Maximum depth for recursion.
    ///
    int mMaxDepth;

    ///
    /// @name mBackground
    ///
    /// @description
    ///		Background color for the scene.
    ///    
    Color mBackground;

    ///
    /// @name mPhongShader
    ///
    /// @description
    ///		Shader to use for local illumination.
    ///
    PhongShader mPhongShader;

    ///
    /// @name mShapes
    ///
    /// @description
    ///		Vector of shapes in the scene.
    ///    
    vector<Shape*> mShapes;

};  // class Raytracer 

}   // namespace Raytracer_n

#endif




