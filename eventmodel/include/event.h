#ifndef ABSIM_EVENT_H
#define ABSIM_EVENT_H

#include "particle.h"
#include "decay.h"
#include "beam.h"
#include "decaydescriptor.h"
#include "msgservice.h"

#include <vector>

namespace ABSIM {

  class Event
  {
  private:
    int_t       n_;
    int_t       ndecays_;
    Particle* particles_;
    Decay*    decays_;

  public:
    static std::string NAME() { return "Event"; }

    Event() = default;
    Event(const DecayDescriptor& descriptor);
    ~Event() {}

    void reset();

    void generate();

    void reDecay(const int_t& i);

    // Getters.
    Particle* particles() { return particles_; }
    Particle& particle(const int_t i)
    {
      if ( i > n_ ) warning() << "Bad index " << i << leave;
      return particles_[i];
    }
    Decay*    decays()    { return decays_; }
    Decay&    decay(const int_t i)
    {
      if ( i > ndecays_ ) warning() << "Bad index " << i << leave;
      return decays_[i];
    }
  };

} // namespace ABSIM

#endif