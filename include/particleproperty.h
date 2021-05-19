#ifndef ABSIM_PARTICLEPROPERTY_H
#define ABSIM_PARTICLEPROPERTY_H

#include "types.h"

#include <tuple>

namespace ABSIM {

  struct Property {
    enum Type {
      Generated,
      Reconstructed
    };
  };

  template <typename T>
  struct ParticleProperty {    
    T gen_;
    T reco_;

    ParticleProperty() :
      gen_( T() ),
      reco_( T() )
    {}
    ParticleProperty(const T& t) :
      gen_( t ),
      reco_( t )
    {}
    ParticleProperty(const T& t_true, const T& t_reco) :
      gen_( t_true ),
      reco_( t_reco )
    {}
    ~ParticleProperty() {}

    // Copy constructor.
    ParticleProperty(const ParticleProperty<T>& rhs);
    // Move constructor.
    ParticleProperty<T>& operator=(const ParticleProperty<T>& rhs);
    ParticleProperty<T>& operator=(const std::tuple<T,T>& rhs);
    ParticleProperty<T>& operator=(const T& rhs)
    {
      gen_ = rhs;
      reco_ = rhs;
      return *this;
    }

    // Operators.
    ParticleProperty<T> operator+(const ParticleProperty<T>& rhs);
    ParticleProperty<T> operator-(const ParticleProperty<T>& rhs);
    ParticleProperty<T> operator*(const ParticleProperty<T>& rhs);
    ParticleProperty<T> operator/(const ParticleProperty<T>& rhs);

    T& operator()(Property::Type type)
    {
      switch (type) {
        case Property::Generated:
          return gen_;
        case Property::Reconstructed:
          return reco_;
      }
      return gen_;
    }

    constexpr T generated()     const { return gen_; }
    constexpr T reconstructed() const { return reco_; }
  };

}  // namespace ABSIM

#endif