/*
    RingBuffer.hpp

    Base ring (= circular) buffer class.

    Created by Matteo Desantis on 09/06/2024.
*/

#ifndef RingBuffer_hpp
#define RingBuffer_hpp

#include <cstring>

namespace dspLib {

class RingBuffer
{
public:
    RingBuffer();                    // basic constructor, allocate 48000 samples
    RingBuffer(int length);          // constructor that allocates 'lenght' samples
    ~RingBuffer();                   // destructor

    int mRingBufferLength;                  // Ring buffer size
    int mReadIdx, mWriteIdx;                // read write indexes
    double *mRingBufferPtr = nullptr;       // Ring biffer pointer to memory
    void reset();
    void updateReadIndex();
    void updateWriteIndex();

private:
    void commonConstructor();        // Constructor code shared by overloading definitions
    void initRingBufferPtr();
    int updateRingBufferIdx(int index);
};

}   // namespace dspLib

#endif /* RingBuffer_hpp */