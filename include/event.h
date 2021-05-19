#ifndef ABSIM_EVENT_H
#define ABSIM_EVENT_H

#include "particle.h"
#include "decay.h"
#include "memorymanager.h"

#include <vector>

namespace ABSIM {

  class Event
  {
  public:
    Particle* particles_;
    Decay*    decays_;


    static std::string NAME() { return "Event"; }

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