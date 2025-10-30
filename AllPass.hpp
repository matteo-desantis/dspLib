/*
    AllPass.hpp

    First-order lattice allpass filter class.

    Created by Matteo Desantis on 2/01/2021.
*/

#ifndef AllPass_hpp
#define AllPass_hpp

#include <stdio.h>
#include <string.h>

namespace dspLib {

class AllPass : public DelayLine
{
public:
    AllPass();                    // constructor with default allocation of 48000 samples
    AllPass(int length);          // constructor with allocation of 'length' samples
    AllPass(int length, int delaySamples);          // Constructor with delay time samples setting
    AllPass(int length, int delaySamples, int Fs, double frequencyLFO, double modDepth);                              // Constructor with LFO initialization as well, sine shape
    AllPass(int length, int delaySamples, int Fs, double frequencyLFO, double modDepth, enum dspLib::waveform shape); // Constructor with LFO initialization as well
    ~AllPass();                   // destructor
    void reset();
    double processAudio(double sampleIn);
    void setFeedbackCoefficient(double feedbackCoefficient);
private:
    double mFeedbackCoef = 0.5;   // feedback coefficient value
};

}   // namespace dspLib 

#endif /* AllPas_hpp */