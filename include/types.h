#ifndef ABSIM_TYPES_H
#define ABSIM_TYPES_H

#include <cstddef> // std::size_t.
#include <complex>

namespace ABSIM {

  using real_t = float;
  using int_t = unsigned int;
  using complex_t = std::complex<float>;
  using size_t = std::size_t;

} // namespace ABSIM

#endif