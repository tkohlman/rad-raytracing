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

    void set_max_depth(int max_depth) { m_max_depth = max_depth; };

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

    Image *trace_scene(Scene *scene);

private:

    Ray make_reflection_ray(const Vector &normal, const Ray &ray,
                            const Point &intersection);

    Intersection *get_closest_intersection(Scene *scene, const Ray &ray);

    ///
    /// @name mMaxDepth
    ///
    /// @description
    ///		Maximum depth for recursion.
    ///
    int m_max_depth;

    ///
    /// @name mPhongShader
    ///
    /// @description
    ///		Shader to use for local illumination.
    ///
    PhongShader m_phong_shader;

    Point *m_intersection;

};  // class Raytracer

}   // namespace RadRt

#endif
