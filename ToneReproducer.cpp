///
/// @file ToneReproducer.cpp
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

#include "ToneReproducer.h"

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

//
// Run
//
void ToneReproducer::run( PixelBuffer2D *pixels, int algorithm ) {

    prepHDR(pixels);

    if (algorithm == WARDS) {

        wardsTR(pixels);
        applyDevice(pixels);

    } else {

        reinhardsTR(pixels);
    }

    return;

}

//
// PrepHDR
//
void ToneReproducer::prepHDR( PixelBuffer2D *pixels ) {

    // Iterate through each pixel and scale by mLmax
    for (int h(0); h < mHeight; ++h)
    {
        for (int w(0); w < mWidth; ++w)
        {

            pixels->at(h)->at(w) *= mLmax;
        }
    }
}

//
// ApplyDevice
//
void ToneReproducer::applyDevice( PixelBuffer2D *pixels ) {

    // Iterate through each pixel and scale by 1/mLdmax
    for (int h(0); h < mHeight; ++h)
    {
        for (int w(0); w < mWidth; ++w)
        {
            pixels->at(h)->at(w) /= mLdmax;
        }
    }
}

//
// CalcAvgLum
//
float ToneReproducer::calcAvgLum( PixelBuffer2D *pixels ) {

    float sum = 0;
    int n = mHeight * mWidth;

    // Calculate the sum of the luminances
    for (int h(0); h < mHeight; ++h)
    {
        for (int w(0); w < mWidth; ++w)
        {
            sum += log(SIGMA + calcAbsLum(pixels->at(h)->at(w)));
        }
    }

    return exp(sum/n);
}

//
// WardsTR
//
void ToneReproducer::wardsTR( PixelBuffer2D *pixels )
{
    float lavg = calcAvgLum(pixels);
    float sf = 1.219 + powf(mLdmax/2.0, 0.4);
    sf /= (1.219 + powf(lavg, 0.4));
    sf = powf(sf, 2.5);

    // Iterate through each pixel and scale by sf
    for (int h(0); h < mHeight; ++h)
    {
        for (int w(0); w < mWidth; ++w)
        {
            pixels->at(h)->at(w) *= sf;
        }
    }
}

//
// ReinhardsTR
//
void ToneReproducer::reinhardsTR( PixelBuffer2D *pixels )
{
    float sf = ALPHA/calcAvgLum(pixels);

    // Iterate through each pixel and scale by sf
    for (int h(0); h < mHeight; ++h)
    {
        for (int w(0); w < mWidth; ++w)
        {
            pixels->at(h)->at(w) *= sf;
        }
    }
}

}   // namespace RadRt

