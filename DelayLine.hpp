/*
    DelayLine.hpp

    Basic Delay Line algorithm.

    Created by Matteo Desantis on 2/01/2021.
*/

#ifndef DelayLine_hpp
#define DelayLine_hpp

#include "waveforms.hpp"
#include <stdio.h>
#include <string>

namespace dspLib {

class DelayLine : public RingBuffer
{
public:
    DelayLine();                    // constructor with default allocation of 48000 samples
    DelayLine(int length);          // constructor allocation of 'length' samples
    DelayLine(int length, int delaySamples);          // Constructor with delay time samples setting
    DelayLine(int length, int delaySamples, int Fs, double frequencyLFO, double modDepth);                              // Constructor with LFO initialization as well, sine shape
    DelayLine(int length, int delaySamples, int Fs, double frequencyLFO, double modDepth, enum dspLib::waveform shape); // Constructor with LFO initialization as well
    ~DelayLine();                   // destructor

    void reset();
    double processAudio(double sampleIn);
    void setIsModulated(bool isModulated = false);
    void setModDepth(double modDepth = 0.0);
    void setDelaySamples(int delaySamples = 0);
    void updateReadIdx();
    dspLib::LFO mLFO;                       // LFO Object

protected:
    int mDelaySamples;                      // actual delay samples
    bool mIsModulated;                      // Mod status flag
    double mModDepth;                       // Modulation depth (= LFO amplitude)

};
    

}   // namespace dspLib

#endif /* DelayLine_hpp */
