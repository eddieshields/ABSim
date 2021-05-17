#ifndef ABSIM_VERTEX_H
#define ABSIM_VERTEX_H

#include "types.h"

#include <math.h>
#include <cmath>

namespace ABSIM
{

  class Vertex
  {
  private:
    union {
      __m128 intr_;
      struct { real_t x_, y_, z_; };
    };
  public:
    Vertex() :
      x_( -1 ),
      y_( -1 ),
      z_( -1 )
    {}
    Vertex(const real_t& x, const real_t& y, const real_t& z) :
      x_( x ),
      y_( y ),
      z_( z )
    {}
    ~Vertex() {}

    // Copy and Move constructors.
    Vertex(const Vertex& rhs)
    {
      intr_ = rhs.intr_;
    }
    Vertex& operator=(const Vertex& rhs)
    {
      intr_ = rhs.intr_;
      return *this;
    }

    // - operator is only one with a physical meaning.
    real_t operator-(const Vertex& rhs)
    {
      const int dp = 1;
      //_mm_dp_ps( intr_ , rhs.intr_ , dp);
      return sqrtf( dp );
    }

    // Flight distance between two vertices.
    real_t FD(const Vertex& rhs)
    {
      const int dp = 1;
      //_mm_dp_ps( intr_ , rhs.intr_ , dp);
      return sqrtf( dp );
    }
  };

} // namespace ABSIM


#endif