/*
    DelayLine.cpp

    Basic Delay Line algorithm with modulation.

    Created by Matteo Desantis on 2/01/2021.
*/

#include "RingBuffer.hpp"
#include "DelayLine.hpp"
#include "LFO.hpp"
#include "waveforms.hpp"

#include <stdio.h>
#include <math.h>

namespace dspLib {

/* ------------------------------- Constructor ------------------------------ */
DelayLine::DelayLine(): DelayLine::DelayLine(48000){}
DelayLine::DelayLine(int length) : DelayLine::DelayLine(length, 0){}
DelayLine::DelayLine(int length, int delaySamples) : DelayLine::DelayLine(length, delaySamples, 48000, 0.0, 0.0){}
DelayLine::DelayLine(int length, int delaySamples, int Fs, double frequencyLFO, double modDepth) : DelayLine::DelayLine(length, delaySamples, Fs, frequencyLFO, modDepth, sine) {}
DelayLine::DelayLine(int length, int delaySamples, int Fs, double frequencyLFO, double modDepth, enum dspLib::waveform shape) : RingBuffer(length)
{
    // Set delay samples
    setDelaySamples(delaySamples);
    
    // Init according to modulation settings
    if (frequencyLFO == 0.0)
    {
        // No modulation -> LFO freq = 0Hz
        setIsModulated(false);
        setModDepth();
    }
    else
    {
        // Set modulation status flag
        setIsModulated(true);

        // Set modulation depth
        setModDepth(modDepth);

        // Explicitly call base class overloaded constructor and allocate 'length' samples. Also init LFO
        mLFO = dspLib::LFO(Fs, frequencyLFO, shape);
    }
} 

/* ------------------------------ Deconstructor ----------------------------- */
DelayLine::~DelayLine()
{
    // Base class deconstructor is automatically called

    // checks whether LFO object exists
    if (mLFO.mRingBufferPtr)
    {
        mLFO.~LFO();
    }
}
/* -------------------------------------------------------------------------- */


/* -------------------------------------------------------------------------- */
/*                               Public Methods                               */
/* -------------------------------------------------------------------------- */
void DelayLine::reset()
{
    /* ------------ Reset Filter Delay-Line ------------ */
    // Call reset() in base class first
    RingBuffer::reset();

    // No delay
    setDelaySamples();
}

double DelayLine::processAudio(double sampleIn)
{
    /* ------------ Delay Line Processing ------------ */
    // Calculate read index position
    updateReadIdx();
    
    // Delay Algorithm
    double delayOut = mRingBufferPtr[mReadIdx];      // Read delay line at read index
    mRingBufferPtr[mWriteIdx] = sampleIn;            // write input sample at write index
    
    // Update write position index
    updateWriteIndex();

    // Delay algorithm actually reads before writing, so as to avoid to get the old samples the new one is forced to the output when delay time is set to 0
    if (mDelaySamples == 0) delayOut = sampleIn;
    return delayOut;
}

void DelayLine::setIsModulated(bool isModulated)
{
    // Update modulation status flag
    mIsModulated = isModulated;
}

void DelayLine::setModDepth(double modDepth)
{
    // Update modulation status flag
    mModDepth = modDepth;
}

void DelayLine::setDelaySamples(int delaySamples)
{
    // Assign delay samples
    mDelaySamples = delaySamples;
}

void DelayLine::updateReadIdx()
{
    /* ------------ Calculate read index position based on delay samples and modulation amount ------------ */
    mReadIdx = mWriteIdx - mDelaySamples;

    // Delay line modulation
    if (mIsModulated)
    {
        // Modulation of the read position
        mReadIdx = (int)round(mModDepth*mLFO.out() + mReadIdx);

        // Increment LFO object read index 
        mLFO.updateReadIndex();
    }

    // Wrap around the length of the ring buffer
    if(mReadIdx < 0) mReadIdx += mRingBufferLength;
}

}   // namespace dspLib    
