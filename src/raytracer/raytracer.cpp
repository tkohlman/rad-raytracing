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
    mMaxDepth(DEFAULT_MAX_DEPTH)
{
}

Ray Raytracer::makeReflectionRay(const Vector &normal,
                                 const Ray &ray,
                                 const Point &intersection)
{
    Ray reflection(intersection,
                   normalize(
                       vectorSubtract(ray.getDirection(),
                           scalarMultiply(normal,
                               2 * dotProduct(ray.getDirection(), normal)))));
     return reflection;
}

Intersection *Raytracer::getClosestIntersection(Scene *scene, const Ray &ray)
{
    ShapeVector *shapes = scene->getShapes();
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
                (distanceBetween(ray.getVertex(),
                                 intersection->getVertex()) <
                 distanceBetween(ray.getVertex(),
                                 closestIntersection->getIntersectionPoint())))
            {
                // Latest intersection is closer
                if (closestIntersection != nullptr)
                    delete closestIntersection;

                closestIntersection = new Intersection(
                                            intersection->getVertex(),
                                            intersection->getDirection(),
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
    if (depth >= mMaxDepth)
    {
        return scene->getBackground();
    }

    Intersection *intersection = getClosestIntersection(scene, ray);

    // If this ray hits nothing, return the background color
    if (intersection == nullptr)
    {
        return scene->getBackground();
    }

    // local illumination
    Color rv = mPhongShader.shade(scene, intersection);

    float kr = intersection->getIntersectedShape()->getReflectiveConstant();
    float kt = intersection->getIntersectedShape()->getTransmissiveConstant();

    // spawn reflection ray
    if (kr > 0)
    {
        Ray reflection = makeReflectionRay(intersection->getNormal(), ray,
                                           intersection->getIntersectionPoint());
        rv += trace(scene, reflection, depth + 1) * kr;
    }

    // spawn transmission ray
    if (kt > 0)
    {
        float alpha;
        bool insideShape =
            (dotProduct(negateVector(ray.getDirection()), intersection->getNormal()) < 0);

        if (insideShape)
        {
            intersection->setNormal(negateVector(intersection->getNormal()));
            alpha = intersection->getIntersectedShape()->getRefractionIndex();
        }
        else
        {
            alpha = 1.0 / intersection->getIntersectedShape()->getRefractionIndex();
        }

        float cosine = dotProduct(negateVector(ray.getDirection()), intersection->getNormal());

        float discriminant = 1.0 + ( (alpha * alpha) *
            ((cosine * cosine) - 1.0) );

        bool totalInternalReflection = (discriminant < 0);

        if (totalInternalReflection)
        {
            // use the reflection ray with the kt value
            Ray reflection = makeReflectionRay(intersection->getNormal(), ray,
                                               intersection->getIntersectionPoint());
            rv += trace(scene, reflection, depth + 1) * kt;
        }
        else
        {
            // spawn a transmission ray
            Ray transmission(intersection->getIntersectionPoint(),
                             normalize(
                                vectorAdd(scalarMultiply(ray.getDirection(), alpha),
                                    scalarMultiply(intersection->getNormal(),
                                        (alpha * cosine) -
                                            sqrt(discriminant)))));

            rv += trace(scene, transmission, depth + 1) * kt;
        }
    }
    delete intersection;

    return rv;
}

Image *Raytracer::traceScene(Scene *scene)
{
    int height = scene->getHeight();
    int width = scene->getWidth();

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
            Ray ray(scene->getCamera().getLocation(),
                    normalize(Vector((dx * column + xc), (dy * row + yc), -1)));
            Color pixel = trace(scene, ray, INITIAL_DEPTH);

            // Set the color
            image->setPixel(row, column, pixel);
        }
    }

    return image;
}

}   // namespace RadRt
