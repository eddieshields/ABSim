#ifndef ABSIM_PARTICLEALGORITHM_H
#define ABSIM_PARTICLEALGORITHM_H

#include "algorithm.h"
#include "types.h"
#include "particle.h"

namespace ABSIM {
  
  class ParticleAlgorithm : public Algorithm
  {
  private:
    int_t index_;
  public:
    ParticleAlgorithm(std::string name, const int_t index) :
      Algorithm( name ),
      index_( index )
    {}
    ~ParticleAlgorithm() {}

    void operator()(Event& ev) override final
    {
      (*this)(ev.particle(index_));
    }

    virtual void operator()(Particle& particle) = 0;
  };

} // namespace ABSIM

#endif