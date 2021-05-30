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
  events_ = new Event[configuration_.EvtMax];
  auto func = [&](){return this->generate();};
  CLOCK_START;
  invoke_device_function(func,dim3(configuration_.EvtMax,0,0),dim3(0,0,0));
  func();
  CLOCK_STOP;
  CLOCK_TASK( "Generate 1M events" );
}

void ABSim::generate()
{
  for (int i = blockIdx.x; i < configuration_.EvtMax ; i += blockDim.x) {
    events_[i] = Event(descriptor_);
    //events_[i].generate();
  }
  //event->reset();
}