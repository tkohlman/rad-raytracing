///
/// @file ToneReproducer.h
///
/// @author	Thomas Kohlman
/// @date 26 February 2012
///
/// @description
/// 	Contains routines for tone reproduction.
///
/// Version:
/// 	$Id$
///
/// Revisions:
///		$Log$
///
///

#ifndef TONE_REPRODUCER_H
#define TONE_REPRODUCER_H

#include <math.h>
#include <vector>
#include <Color.h>
#include <pixel.h>

#define WARDS       0x01
#define REINHARDS   0x02

namespace RadRt
{

class ToneReproducer
{
public:

    ///
    /// @name ToneReproducer
    ///
    /// @description
    /// 	Constructor
    ///
    /// @param lmax - maximum illuminance of the scene
    /// @param ldmax - maximum illuminance of the display, in nits
    /// @param height - height of the scene, in pixels
    /// @param width - width of the scene, in pixels
    ///
    ToneReproducer( int lmax, int ldmax, int height, int width );

    ///
    /// @name ToneReproducer
    ///
    /// @description
    /// 	Destructor
    ///
    ~ToneReproducer( void );

    ///
    /// @name ToneReproducer
    ///
    /// @description
    /// 	Constructor
    ///
    /// @param pixels - 2D vector of pixels. The array must contain mHeight
    ///                 pointers that each point to mWidth color values.
    /// @param algorithm - the TR algorithm to run (either Ward's or Reinhard's)
    ///
    void run( PixelBuffer2D *pixels, int algorithm );

private:

    ///
    /// @name PrepHDR
    ///
    /// @description
    /// 	Prepares the HDR image by scaling each RGB value by mLmax.
    ///
    /// @param pixels - 2D vector of pixels. The array must contain mHeight
    ///                 pointers that each point to mWidth color values.
    ///
    void prepHDR( PixelBuffer2D *pixels );

    ///
    /// @name CalcAbsLum
    ///
    /// @description
    /// 	Calculates a rought estimate of the absolute illuminance of a
    ///     pixel's RGB value. The estimate is L = 0.27R + 0.67G + 0.06B.
    ///
    /// @param color - a single RGB value
    /// @return - absolute illuminace for this RGB value.
    ///
    inline float calcAbsLum( Color color );

    ///
    /// @name ApplyDevice
    ///
    /// @description
    /// 	Scales each pixel in the scene to the range [0, 1], where 1 is
    ///     represented by mLdmax.
    ///
    /// @param pixels - 2D vector of pixels. The array must contain mHeight
    ///                 pointers that each point to mWidth color values.
    ///
    void applyDevice( PixelBuffer2D *pixels );

    ///
    /// @name CalcAvgLum
    ///
    /// @description
    /// 	Calculates the log average luminance over all pixels in the scene.
    ///
    /// @param pixels - 2D vector of pixels. The array must contain mHeight
    ///                 pointers that each point to mWidth color values.
    /// @return - the average log luminance of the scene.
    ///
    float calcAvgLum( PixelBuffer2D *pixels );

    /// @name WardsTR
    ///
    /// @description
    /// 	Runs Ward's tone reproduction algorithm.
    ///
    /// @param pixels - 2D vector of pixels. The array must contain mHeight
    ///                 pointers that each point to mWidth color values.
    ///
    void wardsTR( PixelBuffer2D *pixels );

    /// @name ReinhardsTR
    ///
    /// @description
    /// 	Runs Reinhard's tone reproduction algorithm.
    ///
    /// @param pixels - 2D vector of pixels. The array must contain mHeight
    ///                 pointers that each point to mWidth color values.
    ///
    void reinhardsTR( PixelBuffer2D *pixels );

    ///
    /// @name mLmax
    ///
    /// @description
    ///		Maximum illuminance of the scene.
    ///
    int mLmax;

    ///
    /// @name mLdmax
    ///
    /// @description
    ///		Maximum illuminance of the display.
    ///
    int mLdmax;

    ///
    /// @name mHeight
    ///
    /// @description
    ///		Height of the scene, in pixels.
    ///
    int mHeight;

    ///
    /// @name mWidth
    ///
    /// @description
    ///		Width of the scene, in pixels.
    ///
    int mWidth;


};  // class ToneReproducer

//
// CalcAbsLum
//
inline float ToneReproducer::calcAbsLum( Color color )
{
    return (0.27 * color.getR()) +
           (0.67 * color.getG()) +
           (0.06 * color.getB());
}

}   // namespace RadRt

#endif





