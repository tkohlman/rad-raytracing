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
    float height =
        sqrt((_cp1.getX() - _cp2.getX()) * (_cp1.getX() - _cp2.getX()) +
             (_cp1.getY() - _cp2.getY()) * (_cp1.getY() - _cp2.getY()) +
             (_cp1.getZ() - _cp2.getZ()) * (_cp1.getZ() - _cp2.getZ()));
    _orient = scalarMultiply(displacementVector(_cp1, _cp2), 1.0/height);
}

// ~Cylinder
Cylinder::~Cylinder() {
}

Vector Cylinder::getSurfaceNormal(Point surface)
{
    return _orient;
}

// Intersect
Point* Cylinder::intersect(const Ray &ray)
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

    Vector delta_p = displacementVector(ray.getVertex(), _cp1);

    Vector common1 = vectorSubtract(ray.getDirection(),
                        scalarMultiply(_orient,
                            dotProduct(ray.getDirection(), _orient)));
    Vector common2 = vectorSubtract(delta_p,
                        scalarMultiply(_orient, dotProduct(delta_p, _orient)));

    float A = dotProduct(common1, common1);
    float B = 2 * dotProduct(common1, common2);
    float C = dotProduct(common2, common2) - (_radius * _radius);

    // The quadratic roots are found using:
    // roots = (-B +- sqrt(B^2 - 4*A*C))/ (2*A)
    //
    // Test the discriminant: B^2 - 4*A*C

    float discriminant = B * B - 4 * A * C;

    float t1 = -1;
    float t2 = -1;

    if (discriminant >= 0) {
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
    if (dotProduct(ray.getDirection(), _orient) != 0) {
        t3 = dotProduct(displacementVector(_cp1, ray.getVertex()), _orient) /
             dotProduct(ray.getDirection(), _orient);
        t4 = dotProduct(displacementVector(_cp2, ray.getVertex()), _orient) /
             dotProduct(ray.getDirection(), _orient);
    }
    //-------------------------------------------------------------------------


    // Create the four intercept points.
    Point *i1 = NULL;
    Point *i2 = NULL;
    Point *i3 = NULL;
    Point *i4 = NULL;

    // Eliminate points with negative t-values
    if (t1 >= 0) {
        i1 = new Point(
                       ray.getVertex().getX() + t1 * ray.getDirection().getX(),
                       ray.getVertex().getY() + t1 * ray.getDirection().getY(),
                       ray.getVertex().getZ() + t1 * ray.getDirection().getZ());
    }
    if (t2 >= 0) {
        i2 = new Point(ray.getVertex().getX() + t2 * ray.getDirection().getX(),
                       ray.getVertex().getY() + t2 * ray.getDirection().getY(),
                       ray.getVertex().getZ() + t2 * ray.getDirection().getZ());
    }
    if (t3 >= 0) {
        i3 = new Point(ray.getVertex().getX() + t3 * ray.getDirection().getX(),
                       ray.getVertex().getY() + t3 * ray.getDirection().getY(),
                       ray.getVertex().getZ() + t3 * ray.getDirection().getZ());
    }
    if (t4 >= 0) {
        i4 = new Point(ray.getVertex().getX() + t4 * ray.getDirection().getX(),
                       ray.getVertex().getY() + t4 * ray.getDirection().getY(),
                       ray.getVertex().getZ() + t4 * ray.getDirection().getZ());
    }

    // Check that the points lie within their respective boundaries.
    // i1 and i2 must be between the two endcaps. i3 and i4 must be
    // contained in the endcaps.
    if ((i1 != NULL) &&
        ((dotProduct(_orient, displacementVector(*i1, _cp1)) > 0) ||
         (dotProduct(_orient, displacementVector(*i1, _cp2)) < 0))) {
        delete i1;
        i1 = NULL;
    }

    if ((i2 != NULL) &&
        ((dotProduct(_orient, displacementVector(*i2, _cp1)) > 0) ||
         (dotProduct(_orient, displacementVector(*i2, _cp2)) < 0))) {
        delete i2;
        i2 = NULL;
    }

    if ((i3 != NULL) &&
        (dotProduct(displacementVector(*i3, _cp1),
                    displacementVector(*i3, _cp1)) >= (_radius * _radius))) {
        delete i3;
        i3 = NULL;
    }

    if ((i4 != NULL) &&
        (dotProduct(displacementVector(*i4, _cp2),
                    displacementVector(*i4, _cp2)) >= (_radius * _radius))) {
        delete i4;
        i4 = NULL;
    }

    // Take the closest remaining point.
    Point* intersect = NULL;
    float t = 1000000;
    if (i1 != NULL && t1 < t) {
        intersect = i1;
        t = t1;
    }
    if (i2 != NULL && t2 < t) {
        intersect = i2;
        t = t2;
    }
    if (i3 != NULL && t3 < t) {
        intersect = i3;
        t = t3;
    }
    if (i4 != NULL && t4 < t) {
        intersect = i4;
        t = t4;
    }

    // Clean up memory
    if ((i1 != NULL) && (i1 != intersect)) delete i1;
    if ((i2 != NULL) && (i2 != intersect)) delete i2;
    if ((i3 != NULL) && (i3 != intersect)) delete i3;
    if ((i4 != NULL) && (i4 != intersect)) delete i4;

    return intersect;
}

Json::Value Cylinder::serialize() const
{
    Json::Value root = Shape::serialize();
    root["type"] = "cylinder";
    root["center_1"] = _cp1.serialize();
    root["center_2"] = _cp2.serialize();
    root["radius"] = _radius;
    return root;
}

void Cylinder::deserialize(const Json::Value &root)
{
    Shape::deserialize(root);
    _cp1.deserialize(root["center_1"]);
    _cp2.deserialize(root["center_2"]);
    _radius = root["radius"].asFloat();
    init();
}

}   // namespace RadRt
