/*
    OnePoleFilter.cpp

    First-order Direct Form 1 low-pass or high-pass filter class.

    Feedback coefficient calculation from https://dsp.stackexchange.com/questions/54086/single-pole-iir-low-pass-filter-which-is-the-correct-formula-for-the-decay-coe

    Created by Matteo Desantis on 22/10/2020.
*/

#include <cmath>

#include "OnePoleFilter.hpp"
#include "mathUtils.hpp"

namespace dspLib {

/* ------------------------------- Constructor ------------------------------ */
OnePoleFilter::OnePoleFilter()
{
    // ----- Init -----
    // Memory sample
    mMemorySample = 0.0;
    // Feedforward and feedback coefficients
    mFeedbackCoef = 1.0;
    mFeedforwardCoef = 1.0 - mFeedbackCoef;
}
/* -------------------------------------------------------------------------- */


/* -------------------------------------------------------------------------- */
/*                               Public Methods                               */
/* -------------------------------------------------------------------------- */
double OnePoleFilter::processAudioLP(double sampleIn)
{
    /* ------------ Low Pass Filter Processing ------------ */
    double lowPassOut = processAudioLowPassProtected(sampleIn);

    return lowPassOut;
}

double OnePoleFilter::processAudioHP(double sampleIn)
{
    /* ------------ High Pass Filter Processing ------------ */
    // Direct Form 1 mid point
    double midPoint = sampleIn + mFeedbackCoef*mMemorySample; 

    // Filter output
    double highPassOut = mFeedbackCoef*(midPoint - mMemorySample);     


    // Solve denormalisation problem
    highPassOut = dspLib::handleDenormals(highPassOut);
    
    // Update memory sample
    mMemorySample = midPoint;
    
    // Passband gain set to 0dB circa
    highPassOut = highPassOut/mFeedbackCoef;
    
    return highPassOut;
}
void OnePoleFilter::setNormalizedCutoffFrequency(float normCutoffFrequency)
{
    // Filter coefficient calculation
    mFeedbackCoef = exp(-normCutoffFrequency);                // -normCutoffFrequency = wc = 2*pi*f/Fs
}

/* -------------------------------------------------------------------------- */
/*                               Protected Mtehods                              */
/* -------------------------------------------------------------------------- */
double OnePoleFilter::processAudioLowPassProtected(double sampleIn)
{
    // Output gain in the passband is kept to 0dB. [mFeedforwardCoef already assigned].
    mFeedforwardCoef = 1 - mFeedbackCoef;                       
    
    // Filter output
    double lowPassOut = mFeedforwardCoef*sampleIn + mFeedbackCoef*mMemorySample; 


    // Solve denormalisation problem
    lowPassOut = dspLib::handleDenormals(lowPassOut);
    
    // Update memory sample
    mMemorySample = lowPassOut;                              
    
    return lowPassOut;
}

}   // namespace dspLib