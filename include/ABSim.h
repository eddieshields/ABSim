#ifndef ABSIM_ABSIM_H
#define ABSIM_ABSIM_H

#include "event.h"
#include "decaydescriptor.h"
#include "memorymanager.h"
#include "msgservice.h"
#include "threadpool.h"
#include "backend.h"
#include "clock.h"
#include "welcome.h"

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
    ThreadPool         threadpool_;

    void allocateMemory();

  public:
    ABSim()
    {
      Welcome::message();
    };
    ABSim(std::string decay) :
      descriptor_( decay )
    {
      Welcome::message();
    }
    ~ABSim() {}

    ABSimConfiguration& operator()() { return configuration_; }

    void run();
    void generate();
  };

}  // namespace ABSIM

#endif