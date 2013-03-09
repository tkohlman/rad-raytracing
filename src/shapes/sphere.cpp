/*
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 */

#include "sphere.h"

namespace RadRt
{

// Intersect
Point* Sphere::intersect(Vector v, Point o)
{
    // This intercept calculation takes the form of the quadratic equation:
    // At^2 + Bt + C = 0, where
    // A is v*v
    // B is 2(o-_center) * d
    // C is (o-c)(0-c) * _radius^2

    Vector origin_center = displacementVector(o, _center);

    float A = dotProduct(v, v);
    float B = dotProduct(origin_center, v) * 2.0;
    float C = dotProduct(origin_center, origin_center) - _radius * _radius;

    // The quadratic roots are found using:
    // roots = (-B +- sqrt(B^2 - 4*A*C))/ (2*A)
    //
    // Test the discriminant: B^2 - 4*A*C

    float discriminant = B * B - 4 * A * C;

    if (discriminant < 0) {
        // no real roots (no intersection)
        return NULL;

    }

    float distance1 = ( -B + sqrt(discriminant) ) / (2 * A);
    float distance2 = ( -B - sqrt(discriminant) ) / (2 * A);

    float t;

    float epsilon = 0.2;

    // Choose the minimum, positive distance
    if ((distance1 > epsilon) && ( (distance1 < distance2) ||
         (distance2 < epsilon) )) {

        t = distance1;

    } else if ((distance2 > epsilon) && ( (distance2 < distance1) ||
                (distance1 < epsilon) )) {

        t = distance2;

    } else {
        return NULL;
    }

    // From the t-value, calculate the intersect point
    float x = o.getX() + t * v.getX();
    float y = o.getY() + t * v.getY();
    float z = o.getZ() + t * v.getZ();

    Point *intersect = new Point(x, y, z);

    return intersect;
}

//
// GetSurfaceNormal
//
Vector Sphere::getSurfaceNormal(Point surface)
{
    Vector rv = displacementVector(surface, _center);
    normalize(rv);
    return rv;
}

Json::Value Sphere::serialize() const
{
    Json::Value root = Shape::serialize();
    root["type"] = "sphere";
    root["center"] = _center.serialize();
    root["radius"] = _radius;
    return root;
}

void Sphere::deserialize(const Json::Value &root)
{
    Shape::deserialize(root);
    _center.deserialize(root["center"]);
    _radius = root["radius"].asFloat();
}

}   // namespace RadRt