/*
    RingBuffer.cpp

    Base ring (= circular) buffer class.

    Created by Matteo Desantis on 09/06/2024.
*/

# include "RingBuffer.hpp"

namespace dspLib {

/* ------------------------------- Constructor ------------------------------ */
RingBuffer::RingBuffer()
{
    // ----- Init -----
    // default n° samples.
    mRingBufferLength = 48000;             

    // Initialization shared by all constructors
    commonConstructor();
}
RingBuffer::RingBuffer(int length)
{
    // ----- Init -----
    // n° samples.
    mRingBufferLength = length;             

    // Initialization shared by all constructors
    commonConstructor();
}

/* ------------------------------ Deconstructor ----------------------------- */
RingBuffer::~RingBuffer()
{
    // Check whether ring-buffer pointer 'mRingBufferPtr' exists and init
    initRingBufferPtr();
}
/* -------------------------------------------------------------------------- */


/* -------------------------------------------------------------------------- */
/*                               Public Methods                               */
/* -------------------------------------------------------------------------- */
void RingBuffer::reset()
{
    /* ------------ Reset Circular Buffer ------------ */
    // Reset ring-buffer Read and Write indexes
    mReadIdx = mWriteIdx = 0;

    // Init ring-buffer array to 0
    memset(mRingBufferPtr, 0, mRingBufferLength*sizeof(double));
}

void RingBuffer::updateReadIndex()
{
    // Increment read position index
    mReadIdx = updateRingBufferIdx(mReadIdx);
}

void RingBuffer::updateWriteIndex()
{
    // Increment write position index
    mWriteIdx = updateRingBufferIdx(mWriteIdx);
}


/* -------------------------------------------------------------------------- */
/*                               Private methods                              */
/* -------------------------------------------------------------------------- */
void RingBuffer::commonConstructor()
{
    /* ------------ Constructor code shared by all constructors ------------ */
    // Check whether ring buffer pointer 'mRingBufferPtr' exists and init
    initRingBufferPtr();

    // Dynamically allocate mRingBufferLength samples
    mRingBufferPtr = new double[mRingBufferLength];
    
    // Initialise array to 0  
    reset();
}

void RingBuffer::initRingBufferPtr()
{
    // Constructor checks whether ring buffer pointer 'mRingBufferPtr' exists
    if(mRingBufferPtr)
    {
        // If it does, pointer is deleted and reinitialized
        delete [] mRingBufferPtr;                    
        mRingBufferPtr = nullptr;                    
    }
}

int RingBuffer::updateRingBufferIdx(int index)
{
    // Increment ring buffer position index
    index++;
    if (index >= mRingBufferLength) index = 0;
    return index;
}

}   // namespace dspLib