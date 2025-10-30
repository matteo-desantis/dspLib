/*
    LFO.hpp

    LFO Class.

    Created by Matteo Desantis on 15/06/2024.
*/

#ifndef LFO_hpp
#define LFO_hpp

#define _USE_MATH_DEFINES
#include <cmath>
#include "waveforms.hpp" 
#include <string>


//#include "RingBuffer.hpp"

namespace dspLib {
 
class LFO : public RingBuffer
{

public:
    LFO();                                                      // init empty lfo                                                       
    LFO(int Fs, double frequencyLFO);                           // constructor of sine lfo with Fs/frequencyLFO samples (1 period).
    LFO(int Fs, double frequencyLFO, enum dspLib::waveform);    // constructor of lfo with Fs/frequencyLFO samples (1 period), waveform chosen with enum.
    ~LFO();                                                     // destructor
    void reset();
    double out();                                            // Output current LFO value

private:
    enum dspLib::waveform mShape;
    void initWaveform();
};

}   // namespace dspLib 

#endif /* LFO_hpp */
