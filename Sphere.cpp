///
/// @file Sphere.cpp
///
/// @author	Thomas Kohlman
/// @date 28 December 2011
///
/// @description
/// 	Implements a sphere from the shape base class.
///
/// Version:
/// 	$Id: Sphere.cpp,v 1.5 2012/01/21 17:39:32 thomas Exp thomas $
///
/// Revisions:
///		$Log: Sphere.cpp,v $
///		Revision 1.5  2012/01/21 17:39:32  thomas
///		Checkpoint 3, working baseline.
///
///		Revision 1.4  2011/12/29 02:25:08  thomas
///		Removed unnecessary dynamic memory.
///
///		Revision 1.3  2011/12/28 19:52:52  thomas
///		Checkpoint 2, genericized shape handling.
///
///		Revision 1.2  2011/12/28 18:47:18  thomas
///		Checkpoint 2, functioning baseline.
///
///		Revision 1.1  2011/12/28 16:55:52  thomas
///		Initial revision
///
///
///

#include <Sphere.h>

namespace RadRt
{

// Sphere
Sphere::Sphere( Point center, float radius,
                Color ambientColor, Color diffuseColor, Color specularColor,
                float ambientConstant, float diffuseConstant,
                float specularConstant, float specularExponent,
                float reflectionValue, float transmissionValue,
                float refractionIndex ) :

    Shape(ambientColor, diffuseColor, specularColor, ambientConstant,
        diffuseConstant, specularConstant, specularExponent,
        reflectionValue, transmissionValue, refractionIndex),
        _center(center), _radius(radius) {
}

// Intersect
Point* Sphere::Intersect(Vector v, Point o)
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
Vector Sphere::GetSurfaceNormal(Point surface)
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
