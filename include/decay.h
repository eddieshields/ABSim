#ifndef ABSIM_DECAY_H
#define ABSIM_DECAY_H

#include "particle.h"
#include "decaydescriptor.h"
#include "genphasespace.h"
#include "memorymanager.h"

#include <array>
#include <vector>

namespace ABSIM {

  const int MAXP_ = 18;

  /**
   * Decay
   * 
   * Class to represent the decay of a particle into N other particles.
   * 
   * @author Edward Shields
   * @date 11/05/2021
   */
  class Decay {
  friend class Event;
  private:
    Particle* mother_;
    Particle* daughters_[MAXP_];
    int       ndaughters_;

    GenPhaseSpace          generator_;

  public:
    static std::string NAME() { return "Decay"; }
    Decay() {}
    ~Decay() {}

    inline void construct(Particle* particles, const DecayInfo& info)
    {
      mother_ = particles + info.mother;
      ndaughters_ = info.ndaughters;
      for(int i = 0; i < info.ndaughters; i++) {
        daughters_[i] = particles + info.daughters[i];
      }
      //setDecay();
    }

    void setDecay();

    void generateDecay();

    void* operator new (size_t size)
    {
      return MemoryManager<Decay>::allocate( size );
    }

    void* operator new[] (size_t size)
    {
      return MemoryManager<Decay>::allocate( size );
    }

    void operator delete (void* deleted)
    {
      MemoryManager<Decay>::free( deleted );
    }
  };

} // namespace ABSIM

#endif