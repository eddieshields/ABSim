#ifndef DALITZMODEL_RANDOM_H
#define DALITZMODEL_RANDOM_H

#include "msgservice.h"
#include "types.h"

#include <random>
#include <map>

namespace DalitzModel {

class Random
{
private:
  static int                                       _seed;
  static std::mt19937_64                           _engine;

  static std::uniform_real_distribution< real_t >  _uniform;
  static std::exponential_distribution < real_t >  _exponential;
  static std::normal_distribution      < real_t >  _normal;
  static std::uniform_int_distribution < int >     _integer;

public:
  static std::mt19937_64& engine()
  {
    return _engine;
  }

  static void setSeed( const unsigned& seed )
  { 
    _seed = seed;
  }

  static const real_t Rnd()
  {
    return _uniform( engine() );
  }

  static const real_t flat   ( const real_t& min = 0.0, const real_t& max = 1.0 )
  {
    return min + ( max - min ) * _uniform( engine() );
  }

  static const real_t uniform( const real_t& min = 0.0, const real_t& max = 1.0 )
  {
    return min + ( max - min ) * _uniform( engine() );
  }

  static const real_t exponential( const real_t& lambda = 1.0 )
  {
    return _exponential( engine() );
  }

  static const real_t normal( const real_t& mu = 0.0, const real_t& sigma = 1.0 )
  {
    return mu + sigma * _normal( engine() );
  }

  static const int integer( const int& a = 0, const int& b = 1 )
  {
    return _integer( engine() );
  }

  static const bool Bool()
  {
    return _integer( engine() );
  }
};

} // namespace DalitzModel

#endif