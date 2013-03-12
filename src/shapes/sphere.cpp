/*
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 */

#include "sphere.h"
#include "ray.h"

namespace RadRt
{

Ray *Sphere::intersect(const Ray &ray)
{
    // This intercept calculation takes the form of the quadratic equation:
    // At^2 + Bt + C = 0, where
    // A is v*v
    // B is 2(o-_center) * d
    // C is (o-c)(0-c) * _radius^2

    Vector origin_center = displacementVector(ray.getVertex(), _center);

    float A = dotProduct(ray.getDirection(), ray.getDirection());
    float B = dotProduct(origin_center, ray.getDirection()) * 2.0;
    float C = dotProduct(origin_center, origin_center) - _radius * _radius;

    // The quadratic roots are found using:
    // roots = (-B +- sqrt(B^2 - 4*A*C))/ (2*A)
    //
    // Test the discriminant: B^2 - 4*A*C

    float discriminant = B * B - 4 * A * C;

    if (discriminant < 0)
    {
        // no real roots (no intersection)
        return nullptr;
    }

    float distance1 = ( -B + sqrt(discriminant) ) / (2 * A);
    float distance2 = ( -B - sqrt(discriminant) ) / (2 * A);

    float t;

    float epsilon = 0.2;

    // Choose the minimum, positive distance
    if ((distance1 > epsilon) && ( (distance1 < distance2) ||
         (distance2 < epsilon) ))
    {
        t = distance1;
    }
    else if ((distance2 > epsilon) && ( (distance2 < distance1) ||
                (distance1 < epsilon) ))
    {
        t = distance2;
    }
    else
    {
        return nullptr;
    }

    // From the t-value, calculate the intersect point
    float x = ray.getVertex().getX() + t * ray.getDirection().getX();
    float y = ray.getVertex().getY() + t * ray.getDirection().getY();
    float z = ray.getVertex().getZ() + t * ray.getDirection().getZ();

    Point intersection(x, y, z);

    Vector normal = normalize(displacementVector(intersection, _center));

    return new Ray(intersection, normal);
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
