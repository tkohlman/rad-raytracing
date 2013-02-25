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
using namespace Raytracer_n;

//
// Constructor
//
Raytracer::Raytracer(int maxDepth, Color background, PhongShader shader,
    vector<Shape*> shapes) :
    mMaxDepth(maxDepth), mBackground(background), mPhongShader(shader),
    mShapes(shapes) {
}

//
// Destructor
//
Raytracer::~Raytracer() { }

//
// Trace
//
Color Raytracer::Trace(Vector ray, Point origin, int depth) {

    if (depth >= mMaxDepth) {
        return mBackground;
    }

    Color rv = mBackground;

    Point *closest = NULL;
    Shape *s = NULL;

    // find the closest intersection
    vector<Shape*>::iterator iter = mShapes.begin();
    for (iter; iter != mShapes.end(); ++iter) {

        // Get the intersection point
        Point *p = (*iter)->Intersect(ray, origin);

        if (p != NULL) {

            // There was an intersection

            if (closest == NULL) {

                // p is closest, by default
                closest = p;
                s = *iter;

            } else if (origin.distance(*p) < origin.distance(*closest)) {

                // p is closer
                closest = p;
                s = *iter;

            }
        }
    }

    // Calculate the phong shade for the closest pixel
    if (s != NULL) {


        // local illumination
        rv = mPhongShader.Shade(s, *closest, origin);

        if (depth < mMaxDepth) {

            float kr = s->GetReflectiveConstant();
            float kt = s->GetTransmissiveConstant();

            // spawn reflection ray
            if (kr > 0) {
                Vector N = normalize(s->GetSurfaceNormal(*closest));
                Vector reflection = normalize(vectorSubtract(ray, scalarMultiply(N, 2 * dotProduct(ray, N))));
                rv += Trace(reflection, *closest, depth + 1) * kr;
            }

            // spawn transmission ray
            if (kt > 0) {

                Vector N = normalize(s->GetSurfaceNormal(*closest));
                float alpha;

                // test inside/outside
                if (dotProduct(negateVector(ray), N) < 0) {

                    // we are inside the shape
                    N = negateVector(N);
                    alpha = s->GetRefractionIndex() / 1.0;

                } else {

                    // we are outside the shape
                    alpha = 1.0 / s->GetRefractionIndex();

                }

                float cosine = dotProduct(negateVector(ray), N);

                float discriminant = 1.0 + ( (alpha * alpha) *
                    ((cosine * cosine) - 1.0) );

                if (discriminant < 0) {

                    // total internal reflection:
                    // use the reflection ray with the kt value
                    Vector reflection = normalize(vectorSubtract(ray, scalarMultiply(N, 2 * dotProduct(ray, N))));
                    rv += Trace(reflection, *closest, depth + 1) * kt;

                } else {

                    // spawn a transmission ray
                    Vector transmission = normalize(
                                            vectorAdd(scalarMultiply(ray, alpha),
                                                scalarMultiply(N,
                                                    (alpha * cosine) - sqrt(discriminant))));

                    rv += Trace(transmission, *closest, depth + 1) * kt;

                }
            }
        }
    }

    return rv;

}
