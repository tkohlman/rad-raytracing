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

    Vector origin_center = displacement_vector(ray.vertex(), m_center);

    float A = dot_product(ray.direction(), ray.direction());
    float B = dot_product(origin_center, ray.direction()) * 2.0;
    float C = dot_product(origin_center, origin_center) - m_radius * m_radius;

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
    Point intersection(ray.vertex(), ray.direction(), t);

    Vector normal = normalize(displacement_vector(intersection, m_center));

    return new Ray(intersection, normal);
}

Json::Value Sphere::serialize() const
{
    Json::Value root = Shape::serialize();
    root["type"] = "sphere";
    root["center"] = m_center.serialize();
    root["radius"] = m_radius;
    return root;
}

void Sphere::deserialize(const Json::Value &root)
{
    Shape::deserialize(root);
    m_center.deserialize(root["center"]);
    m_radius = root["radius"].asFloat();
}

}   // namespace RadRt
