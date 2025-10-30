/*
    DeZipper.hpp

    DeZipper, paramter smoothing class based on 1st order lowpass filtering in OnePoleFilter class.

    Created by Matteo Desantis on 12/10/2025.
*/

#ifndef DeZipper_hpp
#define DeZipper_hpp

namespace dspLib {

class DeZipper : public OnePoleFilter
{
public:
    DeZipper();                    // Constructor
    DeZipper(double amount);
    double processDeZipper(double sampleIn);
    void setDeZippingAmount(double amount);
};

}   // namespace dspLib

#endif /* DeZipper_hpp */