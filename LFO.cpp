/*
    LFO.cpp

    LFO Class.

    Created by Matteo Desantis on 15/06/2024.
*/

#include "RingBuffer.hpp"
#include "LFO.hpp"
#include "mathUtils.hpp"
#include "waveforms.hpp"

namespace dspLib {

/* ------------------------------- Constructor ------------------------------ */
LFO::LFO() : RingBuffer(0)
{
    // Empty LFO init, allocated array with 0 length.
}

LFO::LFO(int Fs, double frequencyLFO) : LFO::LFO(Fs, frequencyLFO, sine)
{
    /* Delegate constructor forcing waveform to be sine */
}

LFO::LFO(int Fs, double frequencyLFO, dspLib::waveform shape) : RingBuffer((int) round(Fs/frequencyLFO))
{
    /*
    Explicitly call base class overloaded constructor and allocate 'length' samples.
    length = (int) round(Fs/frequencyLFO), allocate enough samples to have one period 
    of the LFO fundamental frequency (specified in Hz).
    */

    // Init lfo according to shape.
    mShape = shape;
    initWaveform();

}

/* ------------------------------ Deconstructor ----------------------------- */
LFO::~LFO()
{
    // Base class deconstructor is automatically called
}
/* -------------------------------------------------------------------------- */


/* -------------------------------------------------------------------------- */
/*                               Public Methods                               */
/* -------------------------------------------------------------------------- */
void LFO::reset()
{
    /* ------------ Reset Filter Delay-Line ------------ */
    // Call reset() in base class first
    RingBuffer::reset();

    // Reinit array with waveform
    initWaveform();
}

double LFO::out()
{
    /* ------------ Ouput current LFO value ------------ */
    return mRingBufferPtr[mReadIdx];
}

/* -------------------------------------------------------------------------- */
/*                               Private Methods                              */
/* -------------------------------------------------------------------------- */
void LFO::initWaveform()
{
// Init lfo according to shape.
    switch(mShape)
    {
        case(sine):
            // Init Sine array
            for (int i = 0; i < mRingBufferLength; i++ )
            {
                mRingBufferPtr[i] = sin(2*M_PI*i/mRingBufferLength);
            }
            break;
        case(triangle):
            // TODO:
            break;
        case(saw):
            // TODO:
            break;
        case(sawUpward):
            // TODO:
            break;
        case(square):
            // TODO:
            break;
    }
}

}   // namespace dspLib    
