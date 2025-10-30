/*
    mathUtils.hpp

    Math utility functions.

    Created by Matteo Desantis on 06/2024.

    TODO: see.cpp
*/

#ifndef mathUtils_hpp
#define mathUtils_hpp

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace dspLib {

double lin(double valuedB);                 // Convert from dB (20*log10) to linear values
double handleDenormals(double valueIn);     // Solve denormalisation problems.
double normalizeFreq(double fc, double fs);   // Normalize frequency to [0, 2pi] range

}   // namespace dspLib

#endif /* mathUtils_hpp */ 