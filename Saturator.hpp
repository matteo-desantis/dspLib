/*
    Saturator.hpp

    Inverse-tangent and hyperbolic-tangent based saturation unit.

    Created by Matteo Desantis on 22/10/2020.
*/

#ifndef Saturator_hpp
#define Saturator_hpp

#include <stdio.h>

namespace dspLib {

class Saturator
{
public:
    Saturator();            // Constructor
    double processAudioAtan(double sampleIn);               // Wrapper for saturate(), with atan function
    double processAudioTanh(double sampleIn);               // Wrapper for saturate(), with tanh function
    void setDrive(double drive);                            // set drive from dB to linear scale
private:
    double mDriveLin;
    double saturate(double sampleIn, double (*sigmoidFunction) (double), float addCoef, float multCoef);
};

}   // namespace dspLib

#endif /* Saturator_hpp */