#ifndef ABSIM_ABSIM_H
#define ABSIM_ABSIM_H

#include "event.h"
#include "decaydescriptor.h"
#include "memorymanager.h"
#include "msgservice.h"

namespace ABSIM {

  struct ABSimConfiguration
  {
    int EvtMax = {1000};
    int NThreads = {1};
  };

  class ABSim
  {
  private:
    ABSimConfiguration configuration_;
    DecayDescriptor    descriptor_;

    void allocateMemory();

  public:
    ABSim() = default;
    ABSim(std::string decay) :
      descriptor_( decay )
    {}
    ~ABSim() {}

    ABSimConfiguration& operator()() { return configuration_; }

    void run();
  };

}  // namespace ABSIM

#endif