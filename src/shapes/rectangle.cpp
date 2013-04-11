/*
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 */

#include "rectangle.h"
#include "ray.h"

namespace RadRt
{

void Rectangle::init()
{
    // calculate the normal vector
    Vector v1 = displacement_vector(m_b, m_a);
    Vector v2 = displacement_vector(m_d, m_a);

    m_normal = normalize(cross_product(v2, v1));
}

Ray *Rectangle::intersect(const Ray &ray)
{
    // Check if vector is parallel to plane (no intercept)
    if (dot_product(ray.direction(), m_normal) == 0)
    {
        return nullptr;
    }

    // Find the distance from the ray origin to the intersect point
    float distance = dot_product(displacement_vector(m_a, ray.vertex()),
                                 m_normal) /
                     dot_product(ray.direction(), m_normal);

    if (distance < 0)
    {
        return nullptr;
    }

    // From the distance, calculate the intersect point
    Point intersection(ray.vertex(), ray.direction(), distance);

    // Test to see if the point is inside the rectangle
    Vector CI = displacement_vector(intersection, m_c);
    Vector CB = displacement_vector(m_b, m_c);
    Vector CD = displacement_vector(m_d, m_c);

    if (distance_between(intersection, ray.vertex()) < 0.1)
    {
        return nullptr;
    }
    else if ( (0 <= dot_product(CI, CB)) &&
              (dot_product(CI, CB) < dot_product(CB, CB)) &&
              (0 <= dot_product(CI, CD)) &&
              (dot_product(CI, CD) < dot_product(CD, CD)))
    {
        return new Ray(intersection, m_normal);;
    }

	// does not intersect plane within the rectangle
	return nullptr;
}

Json::Value Rectangle::serialize() const
{
    Json::Value root = Shape::serialize();
    root["type"] = "rectangle";
    root["a"] = m_a.serialize();
    root["b"] = m_b.serialize();
    root["c"] = m_c.serialize();
    root["d"] = m_d.serialize();
    return root;
}

void Rectangle::deserialize(const Json::Value &root)
{
    Shape::deserialize(root);
    m_a.deserialize(root["a"]);
    m_b.deserialize(root["b"]);
    m_c.deserialize(root["c"]);
    m_d.deserialize(root["d"]);
    init();
}

}   // namespace RadRt
