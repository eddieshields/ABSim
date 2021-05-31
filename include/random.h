#ifndef ABSIM_RANDOM_H
#define ABSIM_RANDOM_H

#include "types.h"

#include <random>
#include <thread>

namespace ABSIM {

  class Random
  {
  private:

    thread_local static std::mt19937_64 engine_;

    static std::uniform_real_distribution<real_t>  uniform_;
    static std::exponential_distribution <real_t>  exponential_;
    static std::normal_distribution      <real_t>  normal_;
    static std::uniform_int_distribution <int_t>   integer_;

  public:
    inline static std::mt19937_64& engine()
    {
      return engine_;
    }

    inline static const real_t Rnd()
    {
      return uniform_( engine() );
    }
  
    inline static const real_t flat   ( const real_t& min = 0.0, const real_t& max = 1.0 )
    {
      return min + ( max - min ) * uniform_( engine() );
    }
  
    inline static const real_t uniform( const real_t& min = 0.0, const real_t& max = 1.0 )
    {
      return min + ( max - min ) * uniform_( engine() );
    }
  
    inline static const real_t exponential( const real_t& lambda = 1.0 )
    {
      return exponential_( engine() );
    }
  
    inline static const real_t normal( const real_t& mu = 0.0, const real_t& sigma = 1.0 )
    {
      return mu + sigma * normal_( engine() );
    }
  
    inline static const int_t int_teger( const int_t& a = 0, const int_t& b = 1 )
    {
      return integer_( engine() );
    }
  
    inline static const bool Bool()
    {
      return integer_( engine() );
    }

  };

} // naemspace ABSIM

#endif