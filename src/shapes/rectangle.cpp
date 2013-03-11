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
    Vector v1 = displacementVector(_b, _a);
    Vector v2 = displacementVector(_d, _a);

    _normal = normalize(crossProduct(v2, v1));
}

// Intersect
Point* Rectangle::intersect(const Ray &ray, Vector **normal) {

    // Check if vector is parallel to plane (no intercept)
    if (dotProduct(ray.getDirection(), _normal) == 0) {
        return nullptr;
    }

    // Find the distance from the ray origin to the intersect point
    float distance = dotProduct(displacementVector(_a, ray.getVertex()),
                                 _normal) /
                     dotProduct(ray.getDirection(), _normal);

    if (distance < 0)
    {
        return nullptr;
    }

    // From the distance, calculate the intersect point
    float x = ray.getVertex().getX() + distance * ray.getDirection().getX();
    float y = ray.getVertex().getY() + distance * ray.getDirection().getY();
    float z = ray.getVertex().getZ() + distance * ray.getDirection().getZ();

    Point *intersect = new Point(x, y, z);

    // Test to see if the point is inside the rectangle
    Vector CI = displacementVector(*intersect, _c);
    Vector CB = displacementVector(_b, _c);
    Vector CD = displacementVector(_d, _c);

    if (distanceBetween(*intersect, ray.getVertex()) < 0.1) {
        delete intersect;
        return nullptr;

    } else if ( (0 <= dotProduct(CI, CB)) &&
                (dotProduct(CI, CB) < dotProduct(CB, CB)) &&
                (0 <= dotProduct(CI, CD)) &&
                (dotProduct(CI, CD) < dotProduct(CD, CD))) {

        if (normal != nullptr)
        {
            if (*normal != nullptr)
            {
                delete *normal;
            }
            *normal = new Vector(_normal);
        }

        return intersect;

    } else {
        // does not intersect plane within the rectangle
        delete intersect;
        return nullptr;
    }
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
