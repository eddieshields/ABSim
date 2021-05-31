#ifndef ABSIM_ABSIM_H
#define ABSIM_ABSIM_H

#include "event.h"
#include "decaydescriptor.h"
#include "memorymanager.h"
#include "msgservice.h"
#include "backend.h"
#include "clock.h"

namespace ABSIM {

  struct ABSimConfiguration
  {
    int_t EvtMax = {1000};
    int_t NThreads = {1};
  };

  class ABSim
  {
  private:
    Event*             events_;
    ABSimConfiguration configuration_;
    DecayDescriptor    descriptor_;

    void allocateMemory();

  public:
    ABSim()
    {};
    ABSim(std::string decay) :
      descriptor_( decay )
    {}
    ~ABSim() {}

    ABSimConfiguration& operator()() { return configuration_; }

    void run();
    void generate();
  };

}  // namespace ABSIM

#endif