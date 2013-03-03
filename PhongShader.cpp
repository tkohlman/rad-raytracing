///
/// @file PhongShader.cpp
///
/// @author	Thomas Kohlman
/// @date 3 February 2012
///
/// @description
/// 	Implements a Phong shading model.
///
/// Version:
/// 	$Id$
///
/// Revisions:
///		$Log$
///
///

#include "PhongShader.h"
using namespace Raytracer_n;

//
// Shade
//
Color PhongShader::Shade(Scene *scene, Shape *object, Point intersection)
{
    // Declare the light components
    Color Ka;
    Color Kd;
    Color Ks;

    // Compute the ambient component
    Ka = object->GetAmbientColor(intersection);

    // For each light source
    vector<Light*> *lights = scene->getLights();
    vector<Light*>::iterator light = lights->begin();

    vector<Shape*> *shapes = scene->getShapes();

    for (; light != lights->end(); ++light) {

        // Generate the shadow ray
        Vector shadow_ray = displacementVector((*light)->GetPosition(), intersection);
        shadow_ray = normalize(shadow_ray);

        // Determine if there is direct line of sight to the intersect point
        vector<Shape*>::iterator shape = shapes->begin();
        bool los = true;

        for (; shape != shapes->end(); ++shape) {

            // Do not look at the target object
            if (*shape == object) {
                continue;
            }

            // Get the intersection point
            Point *p = (*shape)->Intersect(shadow_ray, intersection);

            // If this point is closer than the closest known point,
            // there is no line of sight.
            if ((p != NULL) &&
                (distanceBetween(*p, (*light)->GetPosition()) <
                 distanceBetween(intersection, (*light)->GetPosition()))) {

                if ((*shape)->GetTransmissiveConstant() > 0) {
                    continue;
                }

                los = false;
                break;
            }
        }

        if (los) {

            Color oKd = object->GetDiffuseColor(intersection);
            Color oKs = object->GetSpecularColor();
            Color lC = (*light)->GetColor();
            float exp = object->GetSpecularExponent();

            // Calculate the required vectors (normalize all)
            Vector N = normalize(object->GetSurfaceNormal(intersection));

            // Compute dot product between shadow and normal. Clamp to zero
            // if the angle is more than 90 degrees.
            float shadow_dot_normal = dotProduct(shadow_ray, N);
            if (shadow_dot_normal >= 0) {

                // Add in the diffuse component
                Kd += oKd * lC * shadow_dot_normal;

                Vector R = vectorSubtract(shadow_ray, scalarMultiply(N, 2 * shadow_dot_normal));
                normalize(R);
                Vector V = normalize(displacementVector(
                                scene->getCamera().getLocation(), intersection));

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

    Ka = Ka * object->GetAmbientConstant();
    Kd = Kd * object->GetDiffuseConstant();
    Ks = Ks * object->GetSpecularConstant();

    Color rv = Ka + Kd + Ks;

    rv.Clamp();

    return rv;

}






