/*
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 */

#include "tonereproducer.h"

namespace RadRt
{

#define SIGMA 0.01
#define ALPHA 0.16

//
// Constructor
//
ToneReproducer::ToneReproducer( int lmax, int ldmax, int height, int width ) :
    mLmax(lmax), mLdmax(ldmax), mHeight(height), mWidth(width) {
}

//
// Destructor
//
ToneReproducer::~ToneReproducer( void ) {
}

void ToneReproducer::run( Image *image, int algorithm )
{
    prepHDR(image);

    if (algorithm == WARDS)
    {
        wardsTR(image);
        applyDevice(image);
    }
    else
    {
        reinhardsTR(image);
    }

    return;
}

void ToneReproducer::prepHDR( Image *image )
{
    // Iterate through each pixel and scale by mLmax
    for (int h(0); h < mHeight; ++h)
    {
        for (int w(0); w < mWidth; ++w)
        {
            *(image->getPixel(w, h)) *= mLmax;
        }
    }
}

//
// ApplyDevice
//
void ToneReproducer::applyDevice( Image *image )
{
    // Iterate through each pixel and scale by 1/mLdmax
    for (int h(0); h < mHeight; ++h)
    {
        for (int w(0); w < mWidth; ++w)
        {
            *(image->getPixel(w, h)) /= mLdmax;
        }
    }
}

//
// CalcAvgLum
//
float ToneReproducer::calcAvgLum( Image *image )
{
    float sum = 0;
    int n = mHeight * mWidth;

    // Calculate the sum of the luminances
    for (int h(0); h < mHeight; ++h)
    {
        for (int w(0); w < mWidth; ++w)
        {
            sum += log(SIGMA + calcAbsLum(*(image->getPixel(w, h))));
        }
    }

    return exp(sum/n);
}

//
// WardsTR
//
void ToneReproducer::wardsTR( Image *image )
{
    float lavg = calcAvgLum(image);
    float sf = 1.219 + powf(mLdmax/2.0, 0.4);
    sf /= (1.219 + powf(lavg, 0.4));
    sf = powf(sf, 2.5);

    // Iterate through each pixel and scale by sf
    for (int h(0); h < mHeight; ++h)
    {
        for (int w(0); w < mWidth; ++w)
        {
            *(image->getPixel(w, h)) *= sf;
        }
    }
}

//
// ReinhardsTR
//
void ToneReproducer::reinhardsTR( Image *image )
{
    float sf = ALPHA/calcAvgLum(image);

    // Iterate through each pixel and scale by sf
    for (int h(0); h < mHeight; ++h)
    {
        for (int w(0); w < mWidth; ++w)
        {
            *(image->getPixel(w, h)) *= sf;
        }
    }
}

}   // namespace RadRt

