/*
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 */

#include "cylinder.h"
#include "ray.h"

namespace RadRt
{

void Cylinder::init()
{
    float height = distance_between(m_center_point_1, m_center_point_2);
    m_orientation = scalar_multiply(displacement_vector(m_center_point_1, m_center_point_2), 1.0/height);
}

Cylinder::~Cylinder()
{
}

Ray *Cylinder::intersect(const Ray &ray)
{
    // Side intercept ---------------------------------------------------------
    // This intercept calculation takes the form of the quadratic equation:
    // At^2 + Bt + C = 0, where
    // A is (v - (v*orientation) * orientation)^2
    // B is 2( (v - orientation * (v*orientation)) *
    //          (delta_p - (orientation * (delta_p*orientation))))
    // C is (delta_p - (orientation * (delta_p*orientation)))^2 - r^2
    //
    // orientation is (_cp1 - _cp2)
    // delta_p is (o - _cp1)

    Vector3d delta_p = displacement_vector(ray.vertex(), m_center_point_1);

    Vector3d common1 = vector_subtract(ray.direction(),
                        scalar_multiply(m_orientation,
                            dot_product(ray.direction(), m_orientation)));
    Vector3d common2 = vector_subtract(delta_p,
                        scalar_multiply(m_orientation, dot_product(delta_p, m_orientation)));

    float A = dot_product(common1, common1);
    float B = 2 * dot_product(common1, common2);
    float C = dot_product(common2, common2) - (m_radius * m_radius);

    // The quadratic roots are found using:
    // roots = (-B +- sqrt(B^2 - 4*A*C))/ (2*A)
    //
    // Test the discriminant: B^2 - 4*A*C

    float discriminant = B * B - 4 * A * C;

    float t1 = -1;
    float t2 = -1;

    if (discriminant >= 0)
    {
        // Find all possible side intersections
        t1 = ( -B + sqrt(discriminant) ) / (2 * A); // side intersection
        t2 = ( -B - sqrt(discriminant) ) / (2 * A); // side intersection
    }

    // End intercept ----------------------------------------------------------
    // This intercept calculation contains two plane interceptions, and then
    // tests to see if the points lie within the endcaps of the cylinder.
    //

    float t3 = -1;
    float t4 = -1;

    // Find intercepts with both planes
    if (dot_product(ray.direction(), m_orientation) != 0)
    {
        t3 = dot_product(displacement_vector(m_center_point_1, ray.vertex()), m_orientation) /
             dot_product(ray.direction(), m_orientation);
        t4 = dot_product(displacement_vector(m_center_point_2, ray.vertex()), m_orientation) /
             dot_product(ray.direction(), m_orientation);
    }
    //-------------------------------------------------------------------------


    // Create the four intercept points.
    Point3d *i1 = nullptr;
    Point3d *i2 = nullptr;
    Point3d *i3 = nullptr;
    Point3d *i4 = nullptr;

    // Eliminate points with negative t-values
    if (t1 >= 0)
    {
    	i1 = new Point3d(ray.vertex(), ray.direction(), t1);
    }
    if (t2 >= 0)
    {
    	i2 = new Point3d(ray.vertex(), ray.direction(), t2);
    }
    if (t3 >= 0)
    {
        i3 = new Point3d(ray.vertex(), ray.direction(), t3);
    }
    if (t4 >= 0)
    {
        i4 = new Point3d(ray.vertex(), ray.direction(), t4);
    }

    // Check that the points lie within their respective boundaries.
    // i1 and i2 must be between the two endcaps. i3 and i4 must be
    // contained in the endcaps.
    if ((i1 != nullptr) &&
        ((dot_product(m_orientation, displacement_vector(*i1, m_center_point_1)) > 0) ||
         (dot_product(m_orientation, displacement_vector(*i1, m_center_point_2)) < 0)))
    {
        delete i1;
        i1 = nullptr;
    }

    if ((i2 != nullptr) &&
        ((dot_product(m_orientation, displacement_vector(*i2, m_center_point_1)) > 0) ||
         (dot_product(m_orientation, displacement_vector(*i2, m_center_point_2)) < 0)))
    {
        delete i2;
        i2 = nullptr;
    }

    if ((i3 != nullptr) &&
        (dot_product(displacement_vector(*i3, m_center_point_1),
                    displacement_vector(*i3, m_center_point_1)) >= (m_radius * m_radius)))
    {
        delete i3;
        i3 = nullptr;
    }

    if ((i4 != nullptr) &&
        (dot_product(displacement_vector(*i4, m_center_point_2),
                    displacement_vector(*i4, m_center_point_2)) >= (m_radius * m_radius)))
    {
        delete i4;
        i4 = nullptr;
    }

    // Take the closest remaining point.
    Point3d* intersect = nullptr;
    float t = 1000000;
    if (i1 != nullptr && t1 < t)
    {
        intersect = i1;
        t = t1;
    }
    if (i2 != nullptr && t2 < t)
    {
        intersect = i2;
        t = t2;
    }
    if (i3 != nullptr && t3 < t)
    {
        intersect = i3;
        t = t3;
    }
    if (i4 != nullptr && t4 < t)
    {
        intersect = i4;
        t = t4;
    }

    // Clean up memory
    if ((i1 != nullptr) && (i1 != intersect)) delete i1;
    if ((i2 != nullptr) && (i2 != intersect)) delete i2;
    if ((i3 != nullptr) && (i3 != intersect)) delete i3;
    if ((i4 != nullptr) && (i4 != intersect)) delete i4;

    if (intersect != nullptr)
    {
        Ray *rv = new Ray(*intersect, m_orientation);
        delete intersect;
        return rv;
    }
    return nullptr;
}

Json::Value Cylinder::serialize() const
{
    Json::Value root = Shape::serialize();
    root["type"] = "cylinder";
    root["center_1"] = m_center_point_1.serialize();
    root["center_2"] = m_center_point_2.serialize();
    root["radius"] = m_radius;
    return root;
}

void Cylinder::deserialize(const Json::Value &root)
{
    Shape::deserialize(root);
    m_center_point_1.deserialize(root["center_1"]);
    m_center_point_2.deserialize(root["center_2"]);
    m_radius = root["radius"].asFloat();
    init();
}

}   // namespace RadRt
