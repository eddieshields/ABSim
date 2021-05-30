#include "cputhreads.h"

ABSIM::ThreadPool gPool;

GridDimensions gridDim;
thread_local BlockIndices blockIdx;