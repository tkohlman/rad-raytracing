/*
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 */

#include "raytracer.h"
#include "ray.h"
#include "intersection.h"

namespace RadRt
{

const int DEFAULT_MAX_DEPTH = 1;
const int INITIAL_DEPTH = 0;

Raytracer::Raytracer(): mMaxDepth(DEFAULT_MAX_DEPTH) {}

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

PixelBuffer2D *Raytracer::traceScene(Scene *scene)
{
    int height = scene->getHeight();
    int width = scene->getWidth();
    // Calculations to map locations to pixels
    float ratio = float(width)/height;
    float dx = 2.0 * ratio / width;
    float dy = 2.0 / height;
    float xc = -ratio;
    float yc = -1;

    PixelBuffer2D *pixels = new PixelBuffer2D(height);

    // Fire rays for every pixel
    for (int j = dy/2; j < height; ++j)
    {
        pixels->at(j) = new PixelBuffer(width);

        for (int i = dx/2; i < width; ++i)
        {
            // Generate the ray
            Ray ray(scene->getCamera().getLocation(),
                    normalize(Vector((dx * i + xc), (dy * j + yc), -1)));
            Color pixel = trace(scene, ray, INITIAL_DEPTH);

            // Set the color
            pixels->at(j)->at(i) = pixel;
        }
    }

    return pixels;
}

}   // namespace RadRt
