/*
    AllPass.cpp

    First-order lattice allpass filter class.

    Created by Matteo Desantis on 2/01/2021.
*/

#include <cmath>

#include "RingBuffer.hpp"
#include "DelayLine.hpp"
#include "AllPass.hpp"
#include "mathUtils.hpp"

namespace dspLib {

/* ------------------------------- Constructor ------------------------------ */
AllPass::AllPass(){}
AllPass::AllPass(int length) : DelayLine(length){}
AllPass::AllPass(int length, int delaySamples) : DelayLine(length, delaySamples){}
AllPass::AllPass(int length, int delaySamples, int Fs, double frequencyLFO, double modDepth) : AllPass::AllPass(length, delaySamples, Fs, frequencyLFO, modDepth, sine){}
AllPass::AllPass(int length, int delaySamples, int Fs, double frequencyLFO, double modDepth, enum dspLib::waveform shape) : DelayLine(length, delaySamples, Fs, frequencyLFO, modDepth, shape){}

/* ------------------------------- Destructor ------------------------------- */
AllPass::~AllPass()
{
    // Base class deconstructor is automatically called
}
/* -------------------------------------------------------------------------- */
 

/* -------------------------------------------------------------------------- */
/*                               Public Methods                               */
/* -------------------------------------------------------------------------- */
void AllPass::reset()       
{
    /* ------------ Reset Filter Ring buffer ------------ */
    // Call reset() in base class first
    DelayLine::reset();
}

double AllPass::processAudio(double sampleIn)
{
    /* ------------ All Pass Filter Processing ------------ */ 
    // Calculate read index position with inherited DelayLine's modulation logic
    updateReadIdx();


    // Actual All Pass Processing
    double delayLineOut = mRingBufferPtr[mReadIdx];                 // output given by the memory line
    double delayLineIn = sampleIn - delayLineOut*mFeedbackCoef;     // delay line input
    double allPassOut = delayLineIn*mFeedbackCoef + delayLineOut;   // allpass output
    mRingBufferPtr[mWriteIdx] = delayLineIn;                        // actually writes sampleIn the delay array
    
    // Update write position index
    updateWriteIndex();

    // Solve denormalisation problem
    allPassOut = dspLib::handleDenormals(allPassOut);
    
    return allPassOut;
}

void AllPass::setFeedbackCoefficient(double feedbackCoefficient)
{
    // Assign feedback coefficient
    mFeedbackCoef = feedbackCoefficient;     
}

}   // namespace dspLib 