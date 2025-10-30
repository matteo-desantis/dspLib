/*
    waveforms.hpp

    Declaration of enum type for waveforms to be used in the dspLib namespace

    Created by Matteo Desantis on 7/07/2024.
*/

#ifndef waveforms_hpp
#define waveforms_hpp

namespace dspLib {

enum waveform {sine = 0, triangle = 1, saw = 2, sawUpward = 3, square = 4};

} // namespace dspLib

#endif /* waveforms_hpp */