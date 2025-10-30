/*
    Saturator.cpp

    Inverse-tangent and hyperbolic-tangent based saturation unit.

    Created by Matteo Desantis on 22/10/2020.
*/

#include <cmath>

#include "Saturator.hpp"
#include "mathUtils.hpp"

namespace dspLib {

/* ------------------------------- Constructor ------------------------------ */
Saturator::Saturator()
{
    // init
    mDriveLin = 0.1;
}
/* -------------------------------------------------------------------------- */


/* -------------------------------------------------------------------------- */
/*                               Public Methods                               */
/* -------------------------------------------------------------------------- */
double Saturator::processAudioAtan(double sampleIn)
{
    // Saturation with atan() as sigmoid curve. Coefficients for volume normalization are empirically derived.
    double saturatorOut = saturate(sampleIn, atan, 0.9f, 0.1f);
    return saturatorOut;
}

double Saturator::processAudioTanh(double sampleIn)
{
    // Saturation with tanh() as sigmoid curve. Coefficients for volume normalization are empirically derived.
    double saturatorOut = saturate(sampleIn, tanh, 0.7f, 0.3f);
    return saturatorOut;
}

void Saturator::setDrive(double drive)
{
    // Convert drive from dB to linear
    mDriveLin = dspLib::lin(drive);
}

/* -------------------------------------------------------------------------- */
/*                               Private Methods                              */
/* -------------------------------------------------------------------------- */
double Saturator::saturate(double sampleIn, double (*sigmoidFunction) (double), float addCoef, float multCoef)
{
    /* -------- Saturation Processing with the given sigmoid function ------- */
    /* double (*sigmoidFunction) (double) is a pointer to a function that takes a double and returns a double.
       For example, the value passed could be either 'tanh' or '&tanh' (pointer to an object-type.)
    */
    
    // Init output and assign convert drive to linear
    double saturatorOut = 0.0;

    // Saturate
    if (mDriveLin < 1.0)
    {
        saturatorOut = sigmoidFunction(sampleIn*mDriveLin)/sigmoidFunction(mDriveLin);
    }
    else
    {
        // Normalise to avoid volume increase - empirical derivation
        saturatorOut = sigmoidFunction(sampleIn*mDriveLin)/((addCoef + multCoef*mDriveLin)*sigmoidFunction(mDriveLin));
    }
    return saturatorOut;
}

}   // namespace dspLib