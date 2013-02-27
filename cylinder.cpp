
#include "cylinder.h"
using namespace Raytracer_n;

#include <cmath>
using namespace std;

// Cylinder
Cylinder::Cylinder(Point cpoint_1, Point cpoint_2, float radius, Color ambientColor,
        Color diffuseColor, Color specularColor,
        float ambientConstant, float diffuseConstant,
        float specularConstant, float specularExponent,
        float reflectionValue, float transmissionValue,
        float refractionIndex) :
     Shape(ambientColor, diffuseColor, specularColor, ambientConstant,
        diffuseConstant, specularConstant, specularExponent,
        reflectionValue, transmissionValue, refractionIndex),
         _cp1(cpoint_1), _cp2(cpoint_2), _radius(radius) {

    float height = sqrt((_cp1.X() - _cp2.X()) * (_cp1.X() - _cp2.X()) +
                        (_cp1.Y() - _cp2.Y()) * (_cp1.Y() - _cp2.Y()) +
                        (_cp1.Z() - _cp2.Z()) * (_cp1.Z() - _cp2.Z()));
    _orient = scalarMultiply(displacementVector(_cp1, _cp2), 1.0/height);

}

// ~Cylinder
Cylinder::~Cylinder() {
}

Vector Cylinder::GetSurfaceNormal(Point p)
{
    return _orient;
}

// Intersect
Point* Cylinder::Intersect(Vector v, Point o) {

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

    Vector delta_p = displacementVector(o, _cp1);

    Vector common1 = vectorSubtract(v,
                        scalarMultiply(_orient, dotProduct(v, _orient)));
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
    if (dotProduct(v, _orient) != 0) {
        t3 = dotProduct(displacementVector(_cp1, o), _orient) /
             dotProduct(v, _orient);
        t4 = dotProduct(displacementVector(_cp2, o), _orient) /
             dotProduct(v, _orient);
    }
    //-------------------------------------------------------------------------


    // Create the four intercept points.
    Point *i1 = NULL;
    Point *i2 = NULL;
    Point *i3 = NULL;
    Point *i4 = NULL;

    // Eliminate points with negative t-values
    if (t1 >= 0) {
        i1 = new Point(o.X() + t1 * v.X(),
                       o.Y() + t1 * v.Y(),
                       o.Z() + t1 * v.Z());
    }
    if (t2 >= 0) {
        i2 = new Point(o.X() + t2 * v.X(),
                       o.Y() + t2 * v.Y(),
                       o.Z() + t2 * v.Z());
    }
    if (t3 >= 0) {
        i3 = new Point(o.X() + t3 * v.X(),
                       o.Y() + t3 * v.Y(),
                       o.Z() + t3 * v.Z());
    }
    if (t4 >= 0) {
        i4 = new Point(o.X() + t4 * v.X(),
                       o.Y() + t4 * v.Y(),
                       o.Z() + t4 * v.Z());
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

