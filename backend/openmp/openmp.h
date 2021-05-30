#ifndef ABSIM_OPENMP_H
#define ABSIM_OPENMP_H

#include <omp.h>
#include <stdexcept>
#include <cassert>
#include <tuple>

#define __host__
#define __device__
#define __shared__
#define __global__

/**
 * @brief Macro to avoid warnings on Release builds with variables used by asserts.
 */
#define _unused(x) ((void) (x))

struct dim3 {
  unsigned int x = 1;
  unsigned int y = 1;
  unsigned int z = 1;

  dim3() = default;
  dim3(const dim3&) = default;
  dim3(const unsigned int& x) : x(x) {}
  dim3(const unsigned int& x, const unsigned int& y) : x(x), y(y) {}
  dim3(const unsigned int& x, const unsigned int& y, const unsigned int& z) : x(x), y(y), z(z) {}
};

struct GridDimensions {
  unsigned int x = 1;
  unsigned int y = 1;
  unsigned int z = 1;
};

struct BlockIndices {
  unsigned int x = 0;
  unsigned int y = 0;
  unsigned int z = 0;
};

struct BlockDimensions {
  unsigned int x = 1;
  unsigned int y = 1;
  unsigned int z = 1;
};

struct ThreadIndices {
  unsigned int x = 0;
  unsigned int y = 0;
  unsigned int z = 0;
};

extern GridDimensions gridDim;
extern BlockIndices blockIdx;
constexpr BlockDimensions blockDim;
constexpr ThreadIndices threadIdx;

#define threadId_ omp_get_thread_num()
#define threadN_ omp_get_num_threads()

template<class Fn>
void invoke_device_function(
  Fn&& function,
  const dim3& grid_dim,
  const dim3& block_dim)
{
  _unused(block_dim);
  #pragma omp parallel for
    for (unsigned int i = threadId_; i < grid_dim.x; i += threadN_) {
      for (unsigned int j = 0; j < grid_dim.y; ++j) {
        for (unsigned int k = 0; k < grid_dim.z; ++k) {
          blockIdx = {i, j, k};
          function();
        }
      }
    }
}

#endif