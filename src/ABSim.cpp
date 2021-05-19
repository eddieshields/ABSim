#include "ABSim.h"

using namespace ABSIM;

void ABSim::allocateMemory()
{
  int nEv = configuration_.EvtMax;
  MemoryManager<Event>::request( nEv );
  int nP = descriptor_.nparticles() * nEv;
  MemoryManager<Particle>::request( nP );
  int nD = descriptor_.ndecays() * nEv;
  MemoryManager<Decay>::request( nD );
}

void ABSim::run()
{
  allocateMemory();
}