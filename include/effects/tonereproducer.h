/**
 * @file
 * @author Thomas Kohlman
 *
 * @section LICENSE
 *
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 *
 * @section DESCRIPTION
 *
 * This class implements the Ward and Reinhard tone reproduction algorithms.
 */

#ifndef TONE_REPRODUCER_H
#define TONE_REPRODUCER_H

namespace RadRt
{

class Color;
class Image;

class ToneReproducer
{
public:

	/**
	 * Apply Ward's tone reproduction algorithm to an image.
	 *
	 * @param image Image to modify.
	 * @param scene_max_luminance Maximum illuminance of the scene.
	 * @param display_max_luminance Maximum illuminance of the display used to
	 *        view the image.
	 */
    void apply_wards_algorithm(Image *image,
    						   int scene_max_illuminance,
    						   int display_max_illuminance);

    /**
     * Apply Reinhard's tone reproduction algorithm to an image.
     *
     * @param image Image to modify.
     * @param scene_max_illuminace Maximum illuminace of the scene.
     */
    void apply_reinhards_algorithm(Image *image, int scene_max_illuminance);

private:

    /**
     * Convert an image to high-dynamic-range: scale each pixel by the
     * maximum illuminace of the scene.
     *
     * @param image Image to convert.
     * @param scene_max_illuminance Maximum illuminance of the scene.
     */
    void prep_hdr(Image *image, int scene_max_illuminance);

    /**
     * Calculate the absolute illuminance of a pixel's RGB value. The
     * calculation uses the following approximation formula:
     * L = 0.27R + 0.67G + 0.06B.
     *
     * @param color Color with red, green, and blue components.
     */
    inline float calc_abs_lum(const Color &color);

    /**
     * Map the color of each pixel in an image to the range supported by a
     * display device.
     *
     * @param image Image to modify.
     * @param display_max_illuminance Maximum illuminance supported by the
     *        device.
     */
    void apply_device(Image *image, int display_max_illuminance);

    /**
     * Calculate the logarithm average luminance of all pixels in an image.
     *
     * @param image Image to use in the calculation.
     */
    float calc_avg_lum(Image *image);

};  // class ToneReproducer

inline float ToneReproducer::calc_abs_lum(const Color &color)
{
    return (0.27 * color.red()) +
           (0.67 * color.green()) +
           (0.06 * color.blue());
}

}   // namespace RadRt

#endif
