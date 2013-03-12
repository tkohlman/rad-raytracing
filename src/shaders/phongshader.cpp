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
    Ka = intersection->getIntersectedShape()->getAmbientColor(
            intersection->getIntersectionPoint());

    Point point = intersection->getIntersectionPoint();
    Shape *shape = intersection->getIntersectedShape();
    Vector normal = intersection->getNormal();

    float Kt = 1;

    // For each light source
    LightVector *lights = scene->getLights();
    LightIterator light = lights->begin();

    ShapeVector *shapes = scene->getShapes();

    for (; light != lights->end(); ++light) {

        // Generate the shadow ray
        Ray shadow_ray(point,
                       normalize(displacementVector((*light)->getPosition(),
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
                (distanceBetween(intersected->getVertex(), (*light)->getPosition()) <
                 distanceBetween(point, (*light)->getPosition()))) {

                if ((*shape_iter)->getTransmissiveConstant() > 0)
                {
                    Kt *= (*shape_iter)->getTransmissiveConstant();
                    continue;
                }

                los = false;
                break;
            }
        }

        if (los)
        {
            Color oKd = shape->getDiffuseColor(point);
            Color oKs = shape->getSpecularColor();
            Color lC = (*light)->getColor();
            float exp = shape->getSpecularExponent();

            // Compute dot product between shadow and normal. Clamp to zero
            // if the angle is more than 90 degrees.
            float shadow_dot_normal = dotProduct(shadow_ray.getDirection(),
                                                 normal);
            if (shadow_dot_normal >= 0) {

                // Add in the diffuse component
                Kd += oKd * lC * shadow_dot_normal;

                Vector R = normalize(vectorSubtract(shadow_ray.getDirection(),
                                scalarMultiply(normal, 2 * shadow_dot_normal)));

                Vector V = normalize(displacementVector(
                                scene->getCamera().getLocation(),
                                    intersection->getIntersectionPoint()));

                // Compute dot product between reflection ray and viewing ray.
                // Clamp to zero if the angle is more than 90 degrees.
                float reflection_dot_view = -dotProduct(R, V);

                if (reflection_dot_view > 0) {
                    // Add in the specular component
                    Ks += oKs * lC * pow(reflection_dot_view, exp);
                }
            }
        }
    }

    Ka = Ka * Kt * shape->getAmbientConstant();
    Kd = Kd * Kt * shape->getDiffuseConstant();
    Ks = Ks * Kt * shape->getSpecularConstant();

    Color rv = Ka + Kd + Ks;

    rv.clamp();

    return rv;
}

}   // namespace RadRt




