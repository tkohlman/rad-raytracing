///
/// @file Raytracer.cpp
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

#include "Raytracer.h"

namespace RadRt
{

const int DEFAULT_MAX_DEPTH = 1;
const int INITIAL_DEPTH = 0;

Raytracer::Raytracer()
{
    mMaxDepth = DEFAULT_MAX_DEPTH;
}

Vector Raytracer::makeReflectionRay(const Vector &normal,
                                    const Vector &ray)
{
    Vector reflection = normalize(
                            vectorSubtract(ray,
                                scalarMultiply(normal,
                                    2 * dotProduct(ray, normal)
                                )
                            )
                        );
     return reflection;
}

Shape *Raytracer::getClosestShape(Scene *scene, const Vector &ray,
                                  Point &origin)
{
    ShapeVector *shapes = scene->getShapes();
    ShapeIterator iter = shapes->begin();

    Point *closestIntersection = NULL;
    Shape *closestShape = NULL;

    for (; iter != shapes->end(); ++iter)
    {
        // Get the intersection point
        Point *currentIntersection = (*iter)->Intersect(ray, origin);

        if (currentIntersection != NULL)
        {
            // Check if this intersection is closer
            if ((closestIntersection == NULL) ||
                (distanceBetween(origin, *currentIntersection) <
                 distanceBetween(origin, *closestIntersection)))
            {
                // p is closer
                closestIntersection = currentIntersection;
                closestShape = *iter;
            }
        }
    }

    // Update origin so that it is the intersection point
    if (closestIntersection != NULL)
    {
        origin = *closestIntersection;
    }

    return closestShape;
}

Color Raytracer::Trace(Scene *scene, Vector ray, Point origin, int depth)
{
    if (depth >= mMaxDepth)
    {
        return scene->getBackground();
    }

    // Note: If closestShape is not null after this call, origin will be
    // modified and will hold the intersection point on the surface of the
    // intersected object. This point is the origin for the next recursively
    // spawned ray.
    Shape *closestShape = getClosestShape(scene, ray, origin);

    // If this ray hits nothing, return the background color
    if (closestShape == NULL)
    {
        return scene->getBackground();
    }

    // local illumination
    Color rv = mPhongShader.Shade(scene, closestShape, origin);

    float kr = closestShape->GetReflectiveConstant();
    float kt = closestShape->GetTransmissiveConstant();

    Vector normal = normalize(closestShape->GetSurfaceNormal(origin));

    // spawn reflection ray
    if (kr > 0)
    {
        Vector reflection = makeReflectionRay(normal, ray);
        rv += Trace(scene, reflection, origin, depth + 1) * kr;
    }

    // spawn transmission ray
    if (kt > 0)
    {
        float alpha;
        bool insideShape = (dotProduct(negateVector(ray), normal) < 0);

        if (insideShape)
        {
            normal = negateVector(normal);
            alpha = closestShape->GetRefractionIndex();
        }
        else
        {
            alpha = 1.0 / closestShape->GetRefractionIndex();
        }

        float cosine = dotProduct(negateVector(ray), normal);

        float discriminant = 1.0 + ( (alpha * alpha) *
            ((cosine * cosine) - 1.0) );

        bool totalInternalReflection = (discriminant < 0);

        if (totalInternalReflection)
        {
            // use the reflection ray with the kt value
            Vector reflection = makeReflectionRay(normal, ray);
            rv += Trace(scene, reflection, origin, depth + 1) * kt;
        }
        else
        {
            // spawn a transmission ray
            Vector transmission = normalize(
                                    vectorAdd(scalarMultiply(ray, alpha),
                                        scalarMultiply(normal,
                                            (alpha * cosine) - sqrt(discriminant))));

            rv += Trace(scene, transmission, origin, depth + 1) * kt;

        }
    }

    return rv;
}

PixelBuffer2D *Raytracer::TraceScene(Scene *scene)
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
            Vector ray( (dx * i + xc), (dy * j + yc), -1);
            normalize(ray);
            Color pixel = Trace(scene, ray, scene->getCamera().getLocation(),
                                INITIAL_DEPTH);

            // Set the color
            pixels->at(j)->at(i) = pixel;
        }
    }

    return pixels;
}

}   // namespace RadRt
