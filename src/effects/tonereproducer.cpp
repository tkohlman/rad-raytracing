/*
 * @file
 * @author Thomas Kohlman
 *
 * @section LICENSE
 *
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 */

#include "color.h"
#include "image.h"
#include "tonereproducer.h"

#include <math.h>

namespace RadRt
{

void ToneReproducer::apply_wards_algorithm(Image *image,
										   int scene_max_illuminance,
										   int display_max_illuminance)
{
	prep_hdr(image, scene_max_illuminance);

    float lavg = calc_avg_lum(image);
    float sf = 1.219 + powf(display_max_illuminance/2.0, 0.4);
    sf /= (1.219 + powf(lavg, 0.4));

    // Iterate through each pixel and scale by sf
    for (int h(0); h < image->height(); ++h)
    {
        for (int w(0); w < image->width(); ++w)
        {
            *(image->get_pixel(w, h)) *= sf;
        }
    }

    apply_device(image, display_max_illuminance);
}

void ToneReproducer::apply_reinhards_algorithm(Image *image,
		                                       int scene_max_illuminance)
{
	prep_hdr(image, scene_max_illuminance);

	const float ALPHA = 0.16;

    float sf = ALPHA/calc_avg_lum(image);

    // Iterate through each pixel and scale by sf
    for (int h(0); h < image->height(); ++h)
    {
        for (int w(0); w < image->width(); ++w)
        {
            *(image->get_pixel(w, h)) *= sf;
        }
    }
}

void ToneReproducer::prep_hdr(Image *image, int scene_max_illuminance)
{
    // Iterate through each pixel and scale by mLmax
    for (int h(0); h < image->height(); ++h)
    {
        for (int w(0); w < image->width(); ++w)
        {
            *(image->get_pixel(w, h)) *= scene_max_illuminance;
        }
    }
}

void ToneReproducer::apply_device(Image *image, int display_max_illuminance)
{
    // Iterate through each pixel and scale by 1/mLdmax
    for (int h(0); h < image->height(); ++h)
    {
        for (int w(0); w < image->width(); ++w)
        {
            *(image->get_pixel(w, h)) /= display_max_illuminance;
        }
    }
}

float ToneReproducer::calc_avg_lum(Image *image)
{
	const float SIGMA = 0.01;
    float sum = 0;
    int total_pixels = image->height() * image->width();

    // Calculate the sum of the luminances
    for (int h(0); h < image->height(); ++h)
    {
        for (int w(0); w < image->width(); ++w)
        {
            sum += log(SIGMA + calc_abs_lum(*(image->get_pixel(w, h))));
        }
    }

    return exp(sum/total_pixels);
}

}   // namespace RadRt
