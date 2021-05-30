#ifndef ABSIM_THREADS_H
#define ABSIM_THREADS_H

#include "threadpool.h"
#include "msgservice.h"

#include <stdexcept>
#include <cassert>
#include <tuple>
#include <future>
#include <vector>

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
  unsigned int x;
  unsigned int y;
  unsigned int z;
};

struct BlockIndices {
  unsigned int x;
  unsigned int y;
  unsigned int z;
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
extern thread_local BlockIndices blockIdx;
constexpr BlockDimensions blockDim;
constexpr ThreadIndices threadIdx;

extern ABSIM::ThreadPool gPool;

template<class Fn>
void invoke_device_function(
  Fn&& function,
  const dim3& grid_dim,
  const dim3& block_dim)
{
  _unused(block_dim);
  std::vector<std::future<void>> returns;
  auto lam = [&] {
    for (unsigned int i = threadId_; i < grid_dim.x; i += threadN_) {
      for (unsigned int j = 0; j < grid_dim.y; ++j) {
        for (unsigned int k = 0; k < grid_dim.z; ++k) {
          blockIdx = {i, j, k};
          function();
        }
      }
    }
  };
  returns.push_back( gPool.submit( lam ) );
  // Wait for threads to finish running.
  for (auto& r : returns) {
    r.get();
  }
}

#endif