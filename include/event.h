#ifndef ABSIM_EVENT_H
#define ABSIM_EVENT_H

#include "particle.h"
#include "decay.h"
#include "beam.h"
#include "decaydescriptor.h"
#include "memorymanager.h"

#include <vector>

namespace ABSIM {

  class Event
  {
  private:
    int       n_;
    int       ndecays_;
    Particle* particles_;
    Decay*    decays_;

  public:
    static std::string NAME() { return "Event"; }

    Event() = default;
    Event(const DecayDescriptor& descriptor);
    ~Event() {}

    void reset();

    void generate();

    void* operator new (size_t size)
    {
      return MemoryManager<Event>::allocate( size );
    }

    void* operator new[] (size_t size)
    {
      return MemoryManager<Event>::allocate( size );
    }

    void operator delete (void* deleted)
    {
      MemoryManager<Event>::free( deleted );
    }
  };

} // namespace ABSIM

#endif