/*
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 */

#ifndef TONE_REPRODUCER_H
#define TONE_REPRODUCER_H

#include <math.h>
#include <vector>
#include "color.h"
#include "image.h"

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
    ~ToneReproducer();

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
    void run(Image *image, int algorithm);

private:

    ///
    /// @name prep_hdr
    ///
    /// @description
    /// 	Prepares the HDR image by scaling each RGB value by mLmax.
    ///
    /// @param pixels - 2D vector of pixels. The array must contain mHeight
    ///                 pointers that each point to mWidth color values.
    ///
    void prep_hdr(Image *image);

    ///
    /// @name calc_abs_lum
    ///
    /// @description
    /// 	Calculates a rought estimate of the absolute illuminance of a
    ///     pixel's RGB value. The estimate is L = 0.27R + 0.67G + 0.06B.
    ///
    /// @param color - a single RGB value
    /// @return - absolute illuminace for this RGB value.
    ///
    inline float calc_abs_lum(Color color);

    ///
    /// @name apply_device
    ///
    /// @description
    /// 	Scales each pixel in the scene to the range [0, 1], where 1 is
    ///     represented by mLdmax.
    ///
    /// @param image - 2D vector of pixels. The array must contain mHeight
    ///                 pointers that each point to mWidth color values.
    ///
    void apply_device(Image *image);

    ///
    /// @name calc_avg_lum
    ///
    /// @description
    /// 	Calculates the log average luminance over all pixels in the scene.
    ///
    /// @param pixels - 2D vector of pixels. The array must contain mHeight
    ///                 pointers that each point to mWidth color values.
    /// @return - the average log luminance of the scene.
    ///
    float calc_avg_lum(Image *image);

    /// @name apply_wards_algorithm
    ///
    /// @description
    /// 	Runs Ward's tone reproduction algorithm.
    ///
    /// @param pixels - 2D vector of pixels. The array must contain mHeight
    ///                 pointers that each point to mWidth color values.
    ///
    void apply_wards_algorithm(Image *image);

    /// @name apply_reinhards_algorithm
    ///
    /// @description
    /// 	Runs Reinhard's tone reproduction algorithm.
    ///
    /// @param pixels - 2D vector of pixels. The array must contain mHeight
    ///                 pointers that each point to mWidth color values.
    ///
    void apply_reinhards_algorithm(Image *image);

    ///
    /// @name mLmax
    ///
    /// @description
    ///		Maximum illuminance of the scene.
    ///
    int m_lmax;

    ///
    /// @name mLdmax
    ///
    /// @description
    ///		Maximum illuminance of the display.
    ///
    int m_ldmax;

    ///
    /// @name mHeight
    ///
    /// @description
    ///		Height of the scene, in pixels.
    ///
    int m_height;

    ///
    /// @name mWidth
    ///
    /// @description
    ///		Width of the scene, in pixels.
    ///
    int m_width;


};  // class ToneReproducer

inline float ToneReproducer::calc_abs_lum( Color color )
{
    return (0.27 * color.red()) +
           (0.67 * color.green()) +
           (0.06 * color.blue());
}

}   // namespace RadRt

#endif





