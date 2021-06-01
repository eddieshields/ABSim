#ifndef ABSIM_DECAYALGORITHM_H
#define ABSIM_DECAYALGORITHM_H

#include "algorithm.h"
#include "decay.h"

namespace ABSIM {
  

  
  class DecayAlgorithm : public Algorithm
  {
  private:
    int_t index_;
  public:
    DecayAlgorithm(std::string name, const int_t index) :
      Algorithm( name ),
      index_( index )
    {}
    ~DecayAlgorithm() {}

    void operator()(Event& ev) override final
    {
      (*this)(ev.decay(index_));
    }

    virtual void operator()(Decay& decay) = 0;
  };

} // namespace ABSIM

#endif