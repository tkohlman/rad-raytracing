#ifndef PIXEL_H_INCLUDED
#define PIXEL_H_INCLUDED

#include <vector>
#include <Color.h>

namespace RadRt
{

typedef std::vector<Color> PixelBuffer;
typedef std::vector< std::vector<Color>* > PixelBuffer2D;

}   // namespace RadRt

#endif // PIXEL_H_INCLUDED
