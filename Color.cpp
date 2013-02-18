///
/// @file Color.cpp
/// 
/// @author	Thomas Kohlman
/// @date 27 December 2011
///
/// @description
/// 	Implements an RGB color representation.
///
/// Version:
/// 	$Id: Color.cpp,v 1.4 2012/01/21 17:36:33 thomas Exp thomas $
/// 
/// Revisions:
///		$Log: Color.cpp,v $
///		Revision 1.4  2012/01/21 17:36:33  thomas
///		Checkpoint 3, working baseline.
///
///		Revision 1.3  2011/12/28 19:52:52  thomas
///		Checkpoint 2, genericized shape handling.
///
///		Revision 1.2  2011/12/28 18:47:18  thomas
///		Checkpoint 2, functioning baseline.
///
///		Revision 1.1  2011/12/27 19:16:49  thomas
///		Initial revision
///
///
///

#include "Color.h"
using namespace Raytracer_n;

// Color
Color::Color(float r, float g, float b) :
    _r(r), _g(g), _b(b) {
}

// Color
Color::Color(const Color& other) :
    _r(other._r), _g(other._g), _b(other._b) {
}

// Color
Color::Color() :
    _r(0), _g(0), _b(0) {
}

// ~Color   
Color::~Color() {
}

// R    
float Color::R() const {
    return (_r);
}

// G  
float Color::G() const {
    return (_g);
}

// B
float Color::B() const {
    return (_b);
}

// operator=
Color& Color::operator=(const Color& other) {
    _r = other.R();
    _g = other.G();
    _b = other.B();
    return *this;
}

// operator<<
ostream& operator<<(ostream& os, const Color& color) {
    os << "(" << color.R() << "r, " << color.G() << "g, " << color.B() << "b)";
    return os;
}




