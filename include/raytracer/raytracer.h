/*
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 */

#ifndef RAYTRACER_H
#define RAYTRACER_H

#define RAY_INFINITY 1000000

#include "color.h"
#include "phongshader.h"
#include "point.h"
#include "shape.h"
#include "vector.h"
#include "image.h"

namespace RadRt
{

class Ray;
class Intersection;

class Raytracer
{
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
    Color trace(Scene *scene, Ray ray, int depth);

    Image *traceScene(Scene *scene);

private:

    Ray makeReflectionRay(const Vector &normal, const Ray &ray,
                          const Point &intersection);

    Intersection *getClosestIntersection(Scene *scene, const Ray &ray);

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

    Point *mIntersection;

};  // class Raytracer

}   // namespace RadRt

#endif




