#ifndef ABSIM_PARTICLEALGORITHM_H
#define ABSIM_PARTICLEALGORITHM_H

#include "algorithm.h"
#include "types.h"

namespace ABSIM {
  
  template <typename EVENT, typename PARTICLE>
  class ParticleAlgorithm : public Algorithm<EVENT>
  {
  private:
    int_t index_;
  public:
    ParticleAlgorithm(std::string name, const int_t index) :
      Algorithm<EVENT>( name ),
      index_( index )
    {}
    ~ParticleAlgorithm() {}

    void operator()(EVENT& ev) override final
    {
      (*this)(ev.particle(index_));
    }

    virtual void operator()(PARTICLE& particle) = 0;
  };

} // namespace ABSIM

#endif