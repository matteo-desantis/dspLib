/*
    DeZipper.cpp

    DeZipper, paramter smoothing class based on 1st order lowpass filtering in OnePoleFilter class.

    Created by Matteo Desantis on 12/10/2025.
*/

#include "OnePoleFilter.hpp"
#include "DeZipper.hpp"

namespace dspLib {

/* ------------------------------- Constructor ------------------------------ */
DeZipper::DeZipper() : DeZipper(0.9) {}
DeZipper::DeZipper(double amount) : OnePoleFilter() 
{
    mFeedbackCoef = amount;
}

/* ------------------------------ Deconstructor ----------------------------- */
DeZipper::~DeZipper(){}
/* -------------------------------------------------------------------------- */


/* -------------------------------------------------------------------------- */
/*                               Public Methods                               */
/* -------------------------------------------------------------------------- */
double DeZipper::processDeZipper(double sampleIn)
{
    /* ------------ De-Zipping (Low Pass) Processing ------------ */
    // feedback coef (= smoothing amount is already set).
    double deZipperOut = processAudioLowPassProtected(sampleIn);
    return deZipperOut;
}

void DeZipper::setDeZippingAmount(double amount)
{
    // Set one pole filters' feedback coefficient equal to dezipping amount
    mFeedbackCoef = amount; 
}

}   // namespace dspLib    
