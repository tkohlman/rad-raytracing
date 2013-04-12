/*
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 */

#include "phongshader.h"
#include "ray.h"
#include "intersection.h"

namespace RadRt
{

Color PhongShader::shade(Scene *scene, Intersection *intersection)
{
    // Declare the light components
    Color Ka;
    Color Kd;
    Color Ks;

    // Compute the ambient component
    Ka = intersection->intersected_shape()->ambient_color(
            intersection->intersection_point());

    Point3d point = intersection->intersection_point();
    Shape *shape = intersection->intersected_shape();
    Vector3d normal = intersection->normal();

    float Kt = 1;

    // For each light source
    LightVector *lights = scene->lights();
    LightIterator light = lights->begin();

    ShapeVector *shapes = scene->shapes();

    for (; light != lights->end(); ++light)
    {
        // Generate the shadow ray
        Ray shadow_ray(point,
                       normalize(displacement_vector((*light)->getPosition(),
                            point)));
        // Determine if there is direct line of sight to the intersect point
        ShapeIterator shape_iter = shapes->begin();
        bool los = true;

        for (; shape_iter != shapes->end(); ++shape_iter)
        {
            // Do not look at the target object
            if (*shape_iter == shape)
            {
                continue;
            }

            // Get the intersection point
            Ray *intersected = (*shape_iter)->intersect(shadow_ray);

            // If this point is closer than the closest known point,
            // there is no line of sight.
            if ((intersected != nullptr) &&
                (distance_between(intersected->vertex(), (*light)->getPosition()) <
                 distance_between(point, (*light)->getPosition())))
            {
                delete intersected;

                if ((*shape_iter)->transmissive_constant() > 0)
                {
                    Kt *= (*shape_iter)->transmissive_constant();
                    continue;
                }

                los = false;
                break;
            }

            if (intersected != nullptr)
                delete intersected;
        }

        if (los)
        {
            Color oKd = shape->diffuse_color(point);
            Color oKs = shape->specular_color();
            Color lC = (*light)->getColor();
            float exp = shape->specular_exponent();

            // Compute dot product between shadow and normal. Clamp to zero
            // if the angle is more than 90 degrees.
            float shadow_dot_normal = dot_product(shadow_ray.direction(),
                                                 normal);
            if (shadow_dot_normal >= 0)
            {
                // Add in the diffuse component
                Kd += oKd * lC * shadow_dot_normal;

                Vector3d R = normalize(vector_subtract(shadow_ray.direction(),
                                scalar_multiply(normal, 2 * shadow_dot_normal)));

                Vector3d V = normalize(displacement_vector(
                                scene->camera().location(),
                                    intersection->intersection_point()));

                // Compute dot product between reflection ray and viewing ray.
                // Clamp to zero if the angle is more than 90 degrees.
                float reflection_dot_view = -dot_product(R, V);

                if (reflection_dot_view > 0)
                {
                    // Add in the specular component
                    Ks += oKs * lC * pow(reflection_dot_view, exp);
                }
            }
        }
    }

    Ka = Ka * Kt * shape->ambient_constant();
    Kd = Kd * Kt * shape->diffuse_constant();
    Ks = Ks * Kt * shape->specular_constant();

    Color rv = Ka + Kd + Ks;

    rv.clamp();

    return rv;
}

}   // namespace RadRt
