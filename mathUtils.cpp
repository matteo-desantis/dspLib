/*
    mathUtils.cpp

    Math utility functions.

    Created by Matteo Desantis on 06/2024.
*/

#include <cmath>

#include "mathUtils.hpp"

namespace dspLib {

/* ------------------------ Convert from dB to Linear ----------------------- */
double lin(double valuedB)
{
    double valueLin = pow(10.0, valuedB/20.0);
    return valueLin;
}

/* ---------------------- Solve denormalisation problem --------------------- */
double handleDenormals(double valueIn)
{
    double absValueIn;

    absValueIn = fabs(valueIn);
    if (absValueIn < 3.e-34)
    {
        valueIn = 0.0;
    }

    return valueIn;
}
/* ------------------- Normalize frequency to [0, 2pi] range ------------------ */
double normalizeFreq(double fc, double fs)
{
    // Clamp frequency to valid range
    if (fc < 0.0) fc = 0.0;

    // Normalize frequency
    double normalizedFreq = 2*M_PI*fc/fs;
    return normalizedFreq;
}

}   // namespace dspLib