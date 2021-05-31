#include "ABSim.h"

using namespace ABSIM;

void ABSim::allocateMemory()
{
  int_t nEv = configuration_.EvtMax;
  MemoryManager<Event>::request( nEv );
  int_t nP = descriptor_.nparticles() * nEv;
  MemoryManager<Particle>::request( nP );
  int_t nD = descriptor_.ndecays() * nEv;
  MemoryManager<Decay>::request( nD );
}

void ABSim::run()
{
  allocateMemory();
  events_ = new Event[configuration_.EvtMax];
  auto func = [&](){return this->generate();};
  CLOCK_START;
  invoke_device_function(func,dim3(configuration_.EvtMax,0,0),dim3(0,0,0));
  func();
  CLOCK_STOP;
  CLOCK_TASK( "Generate 100K events" );
}

void ABSim::generate()
{
  for (int_t i = blockIdx.x; i < configuration_.EvtMax ; i += blockDim.x) {
    events_[i] = Event(descriptor_);
    events_[i].generate();
  }
  //event->reset();
}