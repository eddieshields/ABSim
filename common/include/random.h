#ifndef ABSIM_RANDOM_H
#define ABSIM_RANDOM_H

#include "types.h"

#include <random>
#include <thread>

namespace ABSIM {

  /**
   * @class Random
   * 
   * @brief Random number generator.
   * 
   * @details Thread safe random number generator that can generate numbers according to different distributions.
   * Available distributions are:
   *   - Uniform
   *   - Exponential
   *   - Gaussian
   *   - Bool
   * 
   * @author Edward Shields
   * @date 30/06/2021
   */
  class Random
  {
  private:

    thread_local static std::mt19937_64 engine_;                   ///< Random engine.

    static std::uniform_real_distribution<real_t>  uniform_;       ///< Uniform generator.
    static std::exponential_distribution <real_t>  exponential_;   ///< Exponential generator.
    static std::normal_distribution      <real_t>  normal_;        ///< Gaussian generator.
    static std::uniform_int_distribution <int_t>   integer_;       ///< Integer generator.

  public:
    /**
     * Return the random engine.
     */
    inline static std::mt19937_64& engine()
    {
      return engine_;
    }

    /**
     * Generate random number between 0 and 1.
     */
    inline static const real_t Rnd()
    {
      return uniform_( engine() );
    }
  
    /**
     * Generate a random number according to an uniform distribution.
     * 
     * @param min Minimum
     * @param max Maximum
     */
    inline static const real_t flat( const real_t& min = 0.0, const real_t& max = 1.0 )
    {
      return min + ( max - min ) * uniform_( engine() );
    }
  
    /**
     * Generate a random number according to an uniform distribution.
     * 
     * @param min Minimum
     * @param max Maximum
     */
    inline static const real_t uniform( const real_t& min = 0.0, const real_t& max = 1.0 )
    {
      return min + ( max - min ) * uniform_( engine() );
    }
  
    /**
     * Generate a random number according to an exponential distribution.
     * 
     * @param lambda Lambda
     */
    inline static const real_t exponential( const real_t& lambda = 1.0 )
    {
      return exponential_( engine() );
    }
  
    /**
     * Generate a random number according to a Gaussian distribution.
     * 
     * @param mu Mean
     * @param sigma Width
     */
    inline static const real_t normal( const real_t& mu = 0.0, const real_t& sigma = 1.0 )
    {
      return mu + sigma * normal_( engine() );
    }
  
    /**
     * Generate a random integer according to an uniform distribution.
     * 
     * @param a Minimum
     * @param b Maximum
     */
    inline static const int_t integer( const int_t& a = 0, const int_t& b = 1 )
    {
      return integer_( engine() );
    }
  
    /**
     * Generate a random boolean.
     */
    inline static const bool Bool()
    {
      return integer_( engine() );
    }

  };

} // naemspace ABSIM

#endif