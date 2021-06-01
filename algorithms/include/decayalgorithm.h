#ifndef ABSIM_DECAYALGORITHM_H
#define ABSIM_DECAYALGORITHM_H

#include "algorithm.h"
#include "types.h"

namespace ABSIM {
  
  template <typename EVENT, typename DECAY>
  class DecayAlgorithm : public Algorithm<EVENT>
  {
  private:
    int_t index_;
  public:
    DecayAlgorithm(std::string name, const int_t index) :
      Algorithm<EVENT>( name ),
      index_( index )
    {}
    ~DecayAlgorithm() {}

    void operator()(EVENT& ev) override final
    {
      (*this)(ev.decay(index_));
    }

    virtual void operator()(DECAY& decay) = 0;
  };

} // namespace ABSIM

#endif