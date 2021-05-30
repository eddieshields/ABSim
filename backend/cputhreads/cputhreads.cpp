#include "cputhreads.h"

thread_local unsigned int threadId_;
unsigned int threadN_;
GridDimensions gridDim;
thread_local BlockIndices blockIdx;