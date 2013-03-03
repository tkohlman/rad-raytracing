///
/// @file Rectangle.cpp
///
/// @author	Thomas Kohlman
/// @date 27 December 2011
///
/// @description
/// 	Implements a rectangle from the Shape base class.
///
/// Version:
/// 	$Id: Rectangle.cpp,v 1.5 2012/01/21 17:39:00 thomas Exp thomas $
///
/// Revisions:
///		$Log: Rectangle.cpp,v $
///		Revision 1.5  2012/01/21 17:39:00  thomas
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
///		Revision 1.1  2011/12/27 19:21:25  thomas
///		Initial revision
///
///
///

#include "Rectangle.h"
using namespace Raytracer_n;

// Rectangle
Rectangle::Rectangle( Point a, Point b, Point c, Point d,
        Color ambientColor, Color diffuseColor, Color specularColor,
        float ambientConstant, float diffuseConstant,
        float specularConstant, float specularExponent,
        float reflectionValue, float transmissionValue,
        float refractionIndex ) :

    Shape(ambientColor, diffuseColor, specularColor, ambientConstant,
        diffuseConstant, specularConstant, specularExponent,
        reflectionValue, transmissionValue, refractionIndex),
        _a(a), _b(b), _c(c), _d(d) {

    // calculate the normal vector
    Vector v1 = displacementVector(b, a);
    Vector v2 = displacementVector(d, a);

    _normal = crossProduct(v2, v1);
}

// ~Rectangle
Rectangle::~Rectangle() {
}

// Intersect
Point* Rectangle::Intersect(Vector v, Point o) {

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
    float x = o.X() + distance * v.X();
    float y = o.Y() + distance * v.Y();
    float z = o.Z() + distance * v.Z();

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
Vector Rectangle::GetSurfaceNormal(Point surface)
{
    return _normal;
}

void Rectangle::serialize(std::ostream &os)
{
    os << " rectangle";
    os << " " << _a.X();
    os << " " << _a.Y();
    os << " " << _a.Z();
    os << " " << _b.X();
    os << " " << _b.Y();
    os << " " << _b.Z();
    os << " " << _c.X();
    os << " " << _c.Y();
    os << " " << _c.Z();
    os << " " << _d.X();
    os << " " << _d.Y();
    os << " " << _d.Z();

    Shape::serialize(os);
}
