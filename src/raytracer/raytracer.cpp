/*
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 */

#include "raytracer.h"
#include "ray.h"

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

Shape *Raytracer::getClosestShape(Scene *scene, const Ray &ray,
                                  Point **intersection,
                                  Vector **normal)
{
    ShapeVector *shapes = scene->getShapes();
    ShapeIterator iter = shapes->begin();

    Point *closestIntersection =nullptr;
    Shape *closestShape = nullptr;
    Vector *currentNormal = nullptr;

    for (; iter != shapes->end(); ++iter)
    {
        // Get the intersection point
        Point *currentIntersection = (*iter)->intersect(ray, &currentNormal);

        if (currentIntersection != nullptr)
        {
            // Check if this intersection is closer
            if ((closestIntersection == nullptr) ||
                (distanceBetween(ray.getVertex(), *currentIntersection) <
                 distanceBetween(ray.getVertex(), *closestIntersection)))
            {
                // p is closer
                closestIntersection = currentIntersection;
                closestShape = *iter;

                if (normal != nullptr)
                {
                    if (*normal != nullptr)
                    {
                        delete *normal;
                    }
                    *normal = currentNormal;
                    currentNormal = nullptr;
                }
            }
            else if (currentNormal != nullptr)
            {
                delete currentNormal;
                currentNormal = nullptr;
            }
        }
    }

    // Update the intersection point
    if (closestIntersection != nullptr)
    {
        if (*intersection != nullptr)
        {
            delete *intersection;
        }
        *intersection = closestIntersection;
    }

    return closestShape;
}

Color Raytracer::trace(Scene *scene, Ray ray, int depth)
{
    if (depth >= mMaxDepth)
    {
        return scene->getBackground();
    }

    Point *intersection = nullptr;
    Vector *normal = nullptr;
    Shape *closestShape = getClosestShape(scene, ray, &intersection, &normal);


    // If this ray hits nothing, return the background color
    if (closestShape == nullptr)
    {
        return scene->getBackground();
    }

    // local illumination
    Color rv = mPhongShader.shade(scene, closestShape, *intersection,
                                  *normal);

    float kr = closestShape->getReflectiveConstant();
    float kt = closestShape->getTransmissiveConstant();

    // spawn reflection ray
    if (kr > 0)
    {
        Ray reflection = makeReflectionRay(*normal, ray, *intersection);
        rv += trace(scene, reflection, depth + 1) * kr;
    }

    // spawn transmission ray
    if (kt > 0)
    {
        float alpha;
        bool insideShape =
            (dotProduct(negateVector(ray.getDirection()), *normal) < 0);

        if (insideShape)
        {
            *normal = negateVector(*normal);
            alpha = closestShape->getRefractionIndex();
        }
        else
        {
            alpha = 1.0 / closestShape->getRefractionIndex();
        }

        float cosine = dotProduct(negateVector(ray.getDirection()), *normal);

        float discriminant = 1.0 + ( (alpha * alpha) *
            ((cosine * cosine) - 1.0) );

        bool totalInternalReflection = (discriminant < 0);

        if (totalInternalReflection)
        {
            // use the reflection ray with the kt value
            Ray reflection = makeReflectionRay(*normal, ray, *intersection);
            rv += trace(scene, reflection, depth + 1) * kt;
        }
        else
        {
            // spawn a transmission ray
            Ray transmission(*intersection,
                             normalize(
                                vectorAdd(scalarMultiply(ray.getDirection(), alpha),
                                    scalarMultiply(*normal,
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
