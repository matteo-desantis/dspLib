/*
    OnePoleFilter.hpp

    First-order Direct Form 1 low-pass or high-pass filter class.

    Created by Matteo Desantis on 22/10/2020.
*/

#ifndef OnePoleFilter_hpp
#define OnePoleFilter_hpp

namespace dspLib {

class OnePoleFilter
{
public:
    OnePoleFilter();                    // Constructor
    double processAudioLP(double sampleIn);
    double processAudioHP(double sampleIn);
    void setNormalizedCutoffFrequency(float normCutoffFrequency);
protected:
    float mFeedbackCoef;                // Feedback coefficient
    double processAudioLowPassProtected(double sampleIn);  // Common low pass filtering code shared by processAudioLP() and processDeZipper()

private:
    float mMemorySample;                // Single sample delay line memory
    float mFeedforwardCoef;             // Feedforward coefficient
};

}   // namespace dspLib

#endif /* OnePoleFilter_hpp */