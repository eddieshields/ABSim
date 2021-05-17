#ifndef ABSIM_TYPES_H
#define ABSIM_TYPES_H

#include <cstddef> // std::size_t.
#include <complex>
#include <xmmintrin.h> // Intrinsics.
#include <smmintrin.h>

namespace ABSIM {

  using real_t = float;
  using complex_t = std::complex<float>;
  using size_t = std::size_t;

} // namespace ABSIM

#endif