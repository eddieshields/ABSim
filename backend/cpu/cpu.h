#ifndef ABSIM_CPU_H
#define ABSIM_CPU_H

#include <stdexcept>
#include <cassert>
#include <tuple>

#define __host__
#define __device__
#define __shared__
#define __global__

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


template<class Fn, class Tuple, unsigned long... I>
void invoke_device_function(
  Fn&& function,
  const dim3& grid_dim,
  const dim3& block_dim,
  const Tuple& invoke_arguments,
  std::index_sequence<I...>)
{
  gridDim = {grid_dim.x, grid_dim.y, grid_dim.z};
  for (unsigned int i = 0; i < grid_dim.x; ++i) {
    for (unsigned int j = 0; j < grid_dim.y; ++j) {
      for (unsigned int k = 0; k < grid_dim.z; ++k) {
        blockIdx = {i, j, k};
        function(std::get<I>(invoke_arguments)...);
      }
    }
  }
}

#endif