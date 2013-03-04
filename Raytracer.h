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

typedef vector<Color> PixelBuffer;
typedef vector< vector<Color>* > PixelBuffer2D;

namespace Raytracer_n {

class Raytracer {

public:

    Raytracer();
    ~Raytracer() {};

    void setMaxDepth(int depth) { mMaxDepth = depth; };

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
    Color Trace(Scene *scene, Vector ray, Point origin, int depth);

    PixelBuffer2D *TraceScene(Scene *scene);

private:

    Vector makeReflectionRay(const Vector &normal, const Vector &ray,
                             const Point &intersection);

    Shape *getClosestShape(Scene *scene, const Vector &ray, Point &origin);

    ///
    /// @name mMaxDepth
    ///
    /// @description
    ///		Maximum depth for recursion.
    ///
    int mMaxDepth;

    ///
    /// @name mPhongShader
    ///
    /// @description
    ///		Shader to use for local illumination.
    ///
    PhongShader mPhongShader;

};  // class Raytracer

}   // namespace Raytracer_n

#endif




