/*
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 */

#include "raytracer.h"
#include "ray.h"
#include "intersection.h"
#include "image.h"

namespace RadRt
{

const int DEFAULT_MAX_DEPTH = 1;
const int INITIAL_DEPTH = 0;

Raytracer::Raytracer():
    m_max_depth(DEFAULT_MAX_DEPTH)
{
}

Ray Raytracer::make_reflection_ray(const Vector &normal,
                                 const Ray &ray,
                                 const Point &intersection)
{
    Ray reflection(intersection,
                   normalize(
                       vector_subtract(ray.direction(),
                           scalar_multiply(normal,
                               2 * dot_product(ray.direction(), normal)))));
     return reflection;
}

Intersection *Raytracer::get_closest_intersection(Scene *scene, const Ray &ray)
{
    ShapeVector *shapes = scene->shapes();
    ShapeIterator iter = shapes->begin();
    Intersection *closestIntersection = nullptr;

    for (; iter != shapes->end(); ++iter)
    {
        // Calculate the intersection with this shape
        Ray *intersection = (*iter)->intersect(ray);

        if (intersection != nullptr)
        {
            // Check if this intersection is closer
            if ((closestIntersection == nullptr) ||
                (distance_between(ray.vertex(),
                                 intersection->vertex()) <
                 distance_between(ray.vertex(),
                                 closestIntersection->intersection_point())))
            {
                // Latest intersection is closer
                if (closestIntersection != nullptr)
                    delete closestIntersection;

                closestIntersection = new Intersection(
                                            intersection->vertex(),
                                            intersection->direction(),
                                            *iter);
            }
            delete intersection;
            intersection = nullptr;
        }
    }

    return closestIntersection;
}

Color Raytracer::trace(Scene *scene, Ray ray, int depth)
{
    if (depth >= m_max_depth)
    {
        return scene->background();
    }

    Intersection *intersection = get_closest_intersection(scene, ray);

    // If this ray hits nothing, return the background color
    if (intersection == nullptr)
    {
        return scene->background();
    }

    // local illumination
    Color rv = m_phong_shader.shade(scene, intersection);

    float kr = intersection->intersected_shape()->reflective_constant();
    float kt = intersection->intersected_shape()->transmissive_constant();

    // spawn reflection ray
    if (kr > 0)
    {
        Ray reflection = make_reflection_ray(intersection->normal(), ray,
                                           intersection->intersection_point());
        rv += trace(scene, reflection, depth + 1) * kr;
    }

    // spawn transmission ray
    if (kt > 0)
    {
        float alpha;
        bool insideShape =
            (dot_product(negate_vector(ray.direction()), intersection->normal()) < 0);

        if (insideShape)
        {
            intersection->set_normal(negate_vector(intersection->normal()));
            alpha = intersection->intersected_shape()->refraction_index();
        }
        else
        {
            alpha = 1.0 / intersection->intersected_shape()->refraction_index();
        }

        float cosine = dot_product(negate_vector(ray.direction()), intersection->normal());

        float discriminant = 1.0 + ( (alpha * alpha) *
            ((cosine * cosine) - 1.0) );

        bool totalInternalReflection = (discriminant < 0);

        if (totalInternalReflection)
        {
            // use the reflection ray with the kt value
            Ray reflection = make_reflection_ray(intersection->normal(), ray,
                                               intersection->intersection_point());
            rv += trace(scene, reflection, depth + 1) * kt;
        }
        else
        {
            // spawn a transmission ray
            Ray transmission(intersection->intersection_point(),
                             normalize(
                                vector_add(scalar_multiply(ray.direction(), alpha),
                                    scalar_multiply(intersection->normal(),
                                        (alpha * cosine) -
                                            sqrt(discriminant)))));

            rv += trace(scene, transmission, depth + 1) * kt;
        }
    }
    delete intersection;

    return rv;
}

Image *Raytracer::trace_scene(Scene *scene)
{
    int height = scene->height();
    int width = scene->width();

    // Calculations to map locations to pixels
    float dx = 2.0 / height;
    float dy = 2.0 / height;
    float xc = -float(width)/height;
    float yc = -1;

    std::cout << "dx = " << dx << std::endl;
    std::cout << "dy = " << dy << std::endl;

    Image *image = new Image(width, height);

    // Fire rays for every pixel
    for (int row = 0; row < height; ++row)
    {
        for (int column = 0; column < width; ++column)
        {
            // Generate the ray
            Ray ray(scene->camera().location(),
                    normalize(Vector((dx * column + xc), (dy * row + yc), -1)));
            Color pixel = trace(scene, ray, INITIAL_DEPTH);

            // Set the color
            image->set_pixel(row, column, pixel);
        }
    }

    return image;
}

}   // namespace RadRt
