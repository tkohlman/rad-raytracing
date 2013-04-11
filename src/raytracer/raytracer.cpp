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
    m_max_depth(DEFAULT_MAX_DEPTH),
    m_intersection(nullptr)
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
    Intersection *closest_intersection = nullptr;

    for (; iter != shapes->end(); ++iter)
    {
        // Calculate the intersection with this shape
        Ray *intersection = (*iter)->intersect(ray);

        if (intersection != nullptr)
        {
            // Check if this intersection is closer
            if ((closest_intersection == nullptr) ||
                (distance_between(ray.vertex(),
                                 intersection->vertex()) <
                 distance_between(ray.vertex(),
                                 closest_intersection->intersection_point())))
            {
                // Latest intersection is closer
                if (closest_intersection != nullptr)
                    delete closest_intersection;

                closest_intersection = new Intersection(
                                            intersection->vertex(),
                                            intersection->direction(),
                                            *iter);
            }
            delete intersection;
            intersection = nullptr;
        }
    }

    return closest_intersection;
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

        bool total_internal_reflection = (discriminant < 0);

        if (total_internal_reflection)
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
    int scene_height = scene->height();
    int scene_width = scene->width();

    const float PI = 3.1415926;

    std::cout << "scene width: " << scene_width << std::endl;
    std::cout << "scene height: " << scene_height << std::endl;

    Camera camera = scene->camera();

    float aspect_ratio = float(scene_height) / scene_width;

    std::cout << "aspect ratio: " << aspect_ratio << std::endl;
    std::cout << "focal length: " << camera.focal_length() << std::endl;

    float horizontal_spread = camera.horizontal_spread();
    float vertical_spread = horizontal_spread * aspect_ratio;

    std::cout << "horizontal spread: " << horizontal_spread << std::endl;
    std::cout << "vertical spread: " << vertical_spread << std::endl;

    float projection_width = 2 * camera.focal_length() * tan(horizontal_spread / 180.0 * PI);
    float projection_height = 2 * camera.focal_length() * tan(vertical_spread / 180.0 * PI);

    std::cout << "projection width: " << projection_width << std::endl;
    std::cout << "projection_height: " << projection_height << std::endl;

    float pixel_width = projection_width / scene_width;
    float pixel_height = projection_height / scene_height;

    std::cout << "pixel_width: " << pixel_width << std::endl;
    std::cout << "pixel_height: " << pixel_height << std::endl;

    float pixel_x_0 = (-projection_width / 2) + (pixel_width / 2);
    float pixel_y_0 = (-projection_height / 2) + (pixel_height / 2);

    float current_pixel_x = pixel_x_0;
    float current_pixel_y = pixel_y_0;

    Image *image = new Image(scene_width, scene_height);

    for (int width = 0; width < scene_width; ++width)
    {
    	current_pixel_y = pixel_y_0;

    	for (int height = 0; height < scene_height; ++height)
    	{
            // Generate the ray
            Ray ray(scene->camera().location(),
                    normalize(Vector(current_pixel_x, current_pixel_y,
                    		-camera.focal_length())));
            Color pixel = trace(scene, ray, INITIAL_DEPTH);

            // Set the color
            image->set_pixel(height, width, pixel);


    		current_pixel_y += pixel_height;
    	}

    	current_pixel_x += pixel_width;
    }

    return image;
}

}   // namespace RadRt
