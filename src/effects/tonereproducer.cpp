/*
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 */

#include "tonereproducer.h"

namespace RadRt
{

#define SIGMA 0.01
#define ALPHA 0.16

ToneReproducer::ToneReproducer(int lmax, int ldmax, int height, int width):
    m_lmax(lmax),
    m_ldmax(ldmax),
    m_height(height),
    m_width(width)
{
}

ToneReproducer::~ToneReproducer()
{
}

void ToneReproducer::run(Image *image, int algorithm)
{
    prep_hdr(image);

    if (algorithm == WARDS)
    {
        apply_wards_algorithm(image);
        apply_device(image);
    }
    else
    {
        apply_reinhards_algorithm(image);
    }
}

void ToneReproducer::prep_hdr(Image *image)
{
    // Iterate through each pixel and scale by mLmax
    for (int h(0); h < m_height; ++h)
    {
        for (int w(0); w < m_width; ++w)
        {
            *(image->get_pixel(w, h)) *= m_lmax;
        }
    }
}

void ToneReproducer::apply_device(Image *image)
{
    // Iterate through each pixel and scale by 1/mLdmax
    for (int h(0); h < m_height; ++h)
    {
        for (int w(0); w < m_width; ++w)
        {
            *(image->get_pixel(w, h)) /= m_ldmax;
        }
    }
}

float ToneReproducer::calc_avg_lum(Image *image)
{
    float sum = 0;
    int n = m_height * m_width;

    // Calculate the sum of the luminances
    for (int h(0); h < m_height; ++h)
    {
        for (int w(0); w < m_width; ++w)
        {
            sum += log(SIGMA + calc_abs_lum(*(image->get_pixel(w, h))));
        }
    }

    return exp(sum/n);
}

void ToneReproducer::apply_wards_algorithm( Image *image )
{
    float lavg = calc_avg_lum(image);
    float sf = 1.219 + powf(m_ldmax/2.0, 0.4);
    sf /= (1.219 + powf(lavg, 0.4));
    sf = powf(sf, 2.5);

    // Iterate through each pixel and scale by sf
    for (int h(0); h < m_height; ++h)
    {
        for (int w(0); w < m_width; ++w)
        {
            *(image->get_pixel(w, h)) *= sf;
        }
    }
}

void ToneReproducer::apply_reinhards_algorithm( Image *image )
{
    float sf = ALPHA/calc_avg_lum(image);

    // Iterate through each pixel and scale by sf
    for (int h(0); h < m_height; ++h)
    {
        for (int w(0); w < m_width; ++w)
        {
            *(image->get_pixel(w, h)) *= sf;
        }
    }
}

}   // namespace RadRt
