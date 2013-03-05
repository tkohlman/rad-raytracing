#ifndef CYLINDER_H_INCLUDED
#define CYLINDER_H_INCLUDED

#include "Shape.h"

namespace RadRt
{

class Cylinder : public Shape
{
public:

    Cylinder() {};

    void init();

    ///
    /// @name ~Cylinder
    ///
    /// @description
    /// 	Destructor
    ///
    /// @return - void
    ///
    ~Cylinder();

    Json::Value serialize() const;
    void deserialize(const Json::Value &root);

    ///
    /// @name Intersect
    ///
    /// @description
    /// 	Determines if a ray intersects the cylinder.
    ///
    /// @param v - direction vector of the ray
    /// @param o - origin of the ray
    /// @return - closest (positive) intersect point to the origin of the ray
    ///
    virtual Point* intersect(Vector v, Point o);

    virtual Vector getSurfaceNormal(Point surface);

private:

    ///
    /// @name _cp1
    ///
    /// @description
    ///		The center point of the first base of the cylinder.
    ///
    Point _cp1;

    ///
    /// @name _cp2
    ///
    /// @description
    ///		The center point of the second base of the cylinder.
    ///
    Point _cp2;

    ///
    /// @name _radius
    ///
    /// @description
    ///		The radius of the cylinder.
    ///
    float _radius;

    ///
    /// @name _orient
    ///
    /// @description
    ///		The vector (orientation) formed by the two center points.
    ///
    Vector _orient;

};  // class Cylinder

}   // namespace RadRt

#endif // CYLINDER_H_INCLUDED
