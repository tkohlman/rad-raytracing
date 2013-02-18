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
void ToneReproducer::Run( vector< vector<Color*>* > *pixels, int algorithm ) {

    PrepHDR(pixels);
    
    if (algorithm == WARDS) {
    
        WardsTR(pixels);
        ApplyDevice(pixels);
        
    } else {
    
        ReinhardsTR(pixels);    
    }

    return;

}

//
// PrepHDR
//
void ToneReproducer::PrepHDR( vector< vector<Color*>* > *pixels ) {

    // Iterate through each pixel and scale by mLmax
    for (int h(0); h < mHeight; ++h) {
    
        for (int w(0); w < mWidth; ++w) {
        
            *(pixels->at(h)->at(w)) *= mLmax;
        
        }
    
    }
    
    return;

}

//
// ApplyDevice
//
void ToneReproducer::ApplyDevice( vector< vector<Color*>* > *pixels ) {

    // Iterate through each pixel and scale by 1/mLdmax
    for (int h(0); h < mHeight; ++h) {
    
        for (int w(0); w < mWidth; ++w) {
        
            *(pixels->at(h)->at(w)) /= mLdmax;
        
        }
    }
    
    return;
}

//
// CalcAvgLum
//
float ToneReproducer::CalcAvgLum( vector< vector<Color*>* > *pixels ) {

    float sum = 0;
    int n = mHeight * mWidth;
    
    // Calculate the sum of the luminances
    for (int h(0); h < mHeight; ++h) {
    
        for (int w(0); w < mWidth; ++w) {
        
            sum += log(SIGMA + CalcAbsLum(*(pixels->at(h)->at(w))));
        
        }    
    }
    
    return exp(sum/n);

}
    
//
// WardsTR
//
void ToneReproducer::WardsTR( vector< vector<Color*>* > *pixels ) {

    float lavg = CalcAvgLum(pixels);
    float sf = 1.219 + powf(mLdmax/2.0, 0.4);
    sf /= (1.219 + powf(lavg, 0.4));
    sf = powf(sf, 2.5);
    
    // Iterate through each pixel and scale by sf
    for (int h(0); h < mHeight; ++h) {
    
        for (int w(0); w < mWidth; ++w) {
        
            *(pixels->at(h)->at(w)) *= sf;
        
        }
    }

}
    
//
// ReinhardsTR
//
void ToneReproducer::ReinhardsTR( vector< vector<Color*>* > *pixels ) {

    float sf = ALPHA/CalcAvgLum(pixels);
    
    // Iterate through each pixel and scale by sf
    for (int h(0); h < mHeight; ++h) {
    
        for (int w(0); w < mWidth; ++w) {
        
            *(pixels->at(h)->at(w)) *= sf;
        
        }
    }

}
    
    
    
    
    
    
    
    
