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
    Vector v1 = b - a;
    Vector v2 = d - a;
    
    _normal = v2^v1; // cross product
}

// ~Rectangle
Rectangle::~Rectangle() {
}

// Intersect
Point* Rectangle::Intersect(Vector v, Point o) {

    // Check if vector is parallel to plane (no intercept)
    if (v * _normal == 0) {
        return NULL;
    }

    // Find the distance from the ray origin to the intersect point
    float distance = ( (_a - o) * _normal ) / (v * _normal);
    
    if (distance < 0) {
        return NULL;
    }
    
    // From the distance, calculate the intersect point
    float x = o.X() + distance * v.X();
    float y = o.Y() + distance * v.Y();
    float z = o.Z() + distance * v.Z();

    Point *intersect = new Point(x, y, z);
  
    // Test to see if the point is inside the rectangle
    Vector CI = *intersect - _c;
    Vector CB = _b - _c;
    Vector CD = _d - _c;
      
    if (intersect->distance(o) < 0.1) {
        delete intersect;
        return NULL;
        
    } else if ( (0 <= (CI * CB)) && ((CI * CB) < (CB * CB)) &&
         (0 <= (CI * CD)) && ((CI * CD) < (CD * CD))) {
        
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
Vector Rectangle::GetSurfaceNormal(Point surface) {
    return _normal;
}

//
// GetAmbientColor
//
Color Rectangle::GetAmbientColor(Point p) {
        return GetDiffuseColor(p);
    /*    
    // Implement a procedural shade of the floor.
    
    float width = _a.distance(_d);
    float height = _a.distance(_b);
    
    Vector AP = p - _a;
    Vector AD = _d - _a;
    Vector AB = _b - _a;
    
    float AdistanceP = AP.Length();
    AP.Normalize();
    AD.Normalize();
    AB.Normalize();
    
    float u = AdistanceP * (AP * AD);
    float v = AdistanceP * (AP * AB);
    
    int U = int(u / 2);
    int V = int(v / 2);
    
    //cout << "u: " << u << endl;
    //cout << "v: " << v << endl;
    //cout << "U: " << U << endl;
    //cout << "V: " << V << endl;
    
    bool oddU = U & 0x01;
    bool oddV = V & 0x01;
    
    //cout << "oddU: " << oddU << endl;
    //cout << "oddV: " << oddV << endl;

    //exit (1);
    if ((oddU && oddV) || (!oddU && !oddV)) {
        return Color(1,0,0);
    } else {
        return Color(1,1,0);
    }
    */
    
    /*
    Color rv(0,0,0);
    
    float width = _a.distance(_d);
    float height = _a.distance(_b);
    
    Vector AC = _c - _a;
    float length = AC.Length()/2;
    AC.Normalize();
    Point center(_a, AC, length);

    float u = _d.distance(p);
    float v = _a.distance(p);
    float w = _b.distance(p);
    float z = _c.distance(p);

    int U = int(u/2);
    int V = int(v/2);
    int W = int(v/2);
    int Z = int(z/2);
    
    bool oddU = U & 0x01;
    bool oddV = V & 0x01;
    bool oddW = W & 0x01;
    bool oddZ = Z & 0x01;

    if ((oddU && !oddV) || (oddU && oddV)) {
        rv += Color(0,0.1,0);
    } else {
        rv += Color(0,0,0.1);
    }
    
    if ((oddZ && !oddW) || (oddZ && oddW)) {
        rv += Color(0,0.1,0);
    } else {
        rv += Color(0,0.1,0.1);
    }
  
    return rv;
    //*/
}

//
// GetDiffuseColor
//
Color Rectangle::GetDiffuseColor(Point p) {
    ///*
    // Implement a procedural shade of the floor.
    
    float width = _a.distance(_d);
    float height = _a.distance(_b);
    
    Vector AP = p - _a;
    Vector AD = _d - _a;
    Vector AB = _b - _a;
    
    float AdistanceP = AP.Length();
    AP.Normalize();
    AD.Normalize();
    AB.Normalize();
    
    float u = AdistanceP * (AP * AD);
    float v = AdistanceP * (AP * AB);

    int U = int(u / 3);
    int V = int(v / 3);
    
    //cout << "u: " << u << endl;
    //cout << "v: " << v << endl;
    //cout << "U: " << U << endl;
    //cout << "V: " << V << endl;
    
    bool oddU = U & 0x01;
    bool oddV = V & 0x01;
    
    //cout << "oddU: " << oddU << endl;
    //cout << "oddV: " << oddV << endl;

    //exit (1);
    if ((oddU && oddV) || (!oddU && !oddV)) {
        return Color(1,0,0);
    } else {
        return Color(1,1,0);
    }
    //*/
/*

    // Implement a circular tesselation
  
    Color rv(0,0,0);
    
    float width = _a.distance(_d);
    float height = _a.distance(_b);
    
    Vector AC = _c - _a;
    float length = AC.Length()/2;
    AC.Normalize();
    Point center(_a, AC, length);

    float u = _d.distance(p);
    float v = _a.distance(p);
    float w = _b.distance(p);
    float z = _c.distance(p);

    int U = int(u/2);
    int V = int(v/2);
    int W = int(v/2);
    int Z = int(z/2);
    
    bool oddU = U & 0x01;
    bool oddV = V & 0x01;
    bool oddW = W & 0x01;
    bool oddZ = Z & 0x01;

    if ((oddU && !oddV) || (oddU && oddV)) {
        rv += Color(0,0.5,0);
    } else {
        rv += Color(0,0,0.5);
    }
    
    if ((oddZ && !oddW) || (oddZ && oddW)) {
        rv += Color(0,0.5,0);
    } else {
        rv += Color(0,0.5,0.5);
    }
    
    return rv;
    //*/
}

//
// GetSpecularColor
//
Color Rectangle::GetSpecularColor(Point p) {
    return mKs;
}


