/*
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 */

#include "rectangle.h"

namespace RadRt
{

void Rectangle::init()
{
    // calculate the normal vector
    Vector v1 = displacementVector(_b, _a);
    Vector v2 = displacementVector(_d, _a);

    _normal = crossProduct(v2, v1);
}

// Intersect
Point* Rectangle::intersect(Vector v, Point o) {

    // Check if vector is parallel to plane (no intercept)
    if (dotProduct(v, _normal) == 0) {
        return NULL;
    }

    // Find the distance from the ray origin to the intersect point
    float distance = dotProduct(displacementVector(_a, o), _normal) /
                     dotProduct(v, _normal);

    if (distance < 0) {
        return NULL;
    }

    // From the distance, calculate the intersect point
    float x = o.getX() + distance * v.getX();
    float y = o.getY() + distance * v.getY();
    float z = o.getZ() + distance * v.getZ();

    Point *intersect = new Point(x, y, z);

    // Test to see if the point is inside the rectangle
    Vector CI = displacementVector(*intersect, _c);
    Vector CB = displacementVector(_b, _c);
    Vector CD = displacementVector(_d, _c);

    if (distanceBetween(*intersect, o) < 0.1) {
        delete intersect;
        return NULL;

    } else if ( (0 <= dotProduct(CI, CB)) &&
                (dotProduct(CI, CB) < dotProduct(CB, CB)) &&
                (0 <= dotProduct(CI, CD)) &&
                (dotProduct(CI, CD) < dotProduct(CD, CD))) {

        return intersect;

    } else {
        // does not intersect plane within the rectangle
        delete intersect;
        return NULL;
    }
}

//
// GetSurfaceNormal
//
Vector Rectangle::getSurfaceNormal(Point surface)
{
    return _normal;
}

Json::Value Rectangle::serialize() const
{
    Json::Value root = Shape::serialize();
    root["type"] = "rectangle";
    root["a"] = _a.serialize();
    root["b"] = _b.serialize();
    root["c"] = _c.serialize();
    root["d"] = _d.serialize();
    return root;
}

void Rectangle::deserialize(const Json::Value &root)
{
    Shape::deserialize(root);
    _a.deserialize(root["a"]);
    _b.deserialize(root["b"]);
    _c.deserialize(root["c"]);
    _d.deserialize(root["d"]);
    init();
}

}   // namespace RadRt
