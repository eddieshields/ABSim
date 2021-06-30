#ifndef ABSIM_PARTICLEPROPERTY_H
#define ABSIM_PARTICLEPROPERTY_H

#include "types.h"
#include "properties.h"

#include <tuple>

namespace ABSIM {

  /**
   * @class ParticleProperty
   * 
   * @brief Structure to hold a property of a particle.
   * 
   * @details For each property of a particle generated there are two relevent pieces of information.
   * The first is what is the generated value of the property and the second in what is the reconstructed
   * value of the property. This structure holds both and allows access to both the generated and reconstructed
   * value through a PropertyType: Property::Generated, and Property::Reconstrcuted.
   * 
   * @author Edward Shields
   * @date 30/06/2021
   */
  template <typename T>
  struct ParticleProperty {    
    T gen_;   ///< Generated value of the property.
    T reco_;  ///< Reconstructed value of the property.

    /**
     * Constructor
     */
    ParticleProperty() :
      gen_( T() ),
      reco_( T() )
    {}

    /**
     * Constructor
     * 
     * @param t Generated value of the property
     */
    ParticleProperty(const T& t) :
      gen_( t ),
      reco_( t )
    {}

    /**
     * Constructor
     * 
     * @param t_true Generated value of the property
     * @param t_reco Reconstructed value of the property
     */
    ParticleProperty(const T& t_true, const T& t_reco) :
      gen_( t_true ),
      reco_( t_reco )
    {}
    ~ParticleProperty() {}

    /**
     * Copy constructor.
     */
    ParticleProperty(const ParticleProperty<T>& rhs);
    
    /**
     * Move constructor.
     */
    ParticleProperty<T>& operator=(const ParticleProperty<T>& rhs);
    ParticleProperty<T>& operator=(const std::tuple<T,T>& rhs);
    ParticleProperty<T>& operator=(const T& rhs)
    {
      gen_ = rhs;
      reco_ = rhs;
      return *this;
    }

    // Operators.
    ParticleProperty<T> operator+(const ParticleProperty<T>& rhs); //!< Addition operator.
    ParticleProperty<T> operator-(const ParticleProperty<T>& rhs); //!< Subtraction operator.
    ParticleProperty<T> operator*(const ParticleProperty<T>& rhs); //!< Multiplication operator.
    ParticleProperty<T> operator/(const ParticleProperty<T>& rhs); //!< Division operator.

    /**
     * Access generated or reconstructed value of the property.
     * 
     * @param type Type ot be returned: Generated or Reconstructed.
     */
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

    constexpr T generated()     const { return gen_; }  //!< Return generated value.
    constexpr T reconstructed() const { return reco_; } //!< Return reconstructed value.
  };

}  // namespace ABSIM

#endif