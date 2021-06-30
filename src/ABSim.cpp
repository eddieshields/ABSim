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
  CLOCK_START;
  fillTree();
  CLOCK_STOP;
  CLOCK_TASK("Fill tree with 100K events");
  writer_.tree()->Print();
}


void ABSim::generate()
{
  for (int_t i = blockIdx.x; i < configuration_.EvtMax ; i += blockDim.x) {
    Event& ev = events_[i];
    ev = Event(descriptor_);
    ev.generate();
    sequence_( ev );
  }
}

void ABSim::fillTree()
{
  for(int_t i = 0; i < configuration_.EvtMax; i++) {
    writer_.fill( events_[i] );
  }
}