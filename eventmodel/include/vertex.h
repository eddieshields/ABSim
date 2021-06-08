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
    real_t x_, y_, z_;

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
    Vertex(const Vertex& rhs) :
      x_( rhs.x_ ),
      y_( rhs.y_ ),
      z_( rhs.z_ )
    {}
    Vertex& operator=(const Vertex& rhs)
    {
      x_ = rhs.x_;
      y_ = rhs.y_;
      z_ = rhs.z_;
      return *this;
    }

    inline real_t X() { return x_; }
    inline real_t Y() { return y_; }
    inline real_t Z() { return z_; }

    // - operator is only one with a physical meaning.
    inline real_t operator-(const Vertex& rhs)
    {
      real_t d = ( x_ - rhs.x_ ) + ( y_ - rhs.y_ ) + ( z_ - rhs.z_ );
      return sqrtf( d );
    }

    // Flight distance between two vertices.
    inline real_t FD(const Vertex& rhs)
    {
      real_t d = ( x_ - rhs.x_ ) + ( y_ - rhs.y_ ) + ( z_ - rhs.z_ );
      return sqrtf( d );
    }
  };

} // namespace ABSIM


#endif