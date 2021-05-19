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
  auto func = [&](){return this->generate();};
  CLOCK_START;
  std::vector<std::future<void>> futures;
  for (int i = 0; i < 8; i++) {
    futures.push_back( threadpool_.submit( func ) );
  }
  for (int j = 0; j < 8; j++) {
    futures[j].get();
  }
  CLOCK_STOP;
  CLOCK_TASK( "Generate 1M events" );
}

void ABSim::generate()
{
  Event* event = new Event(descriptor_);
  for (int i = blockIdx.x; i < configuration_.EvtMax - 8; i += 8) {
    event = new Event(descriptor_);
  }
  event->reset();
}