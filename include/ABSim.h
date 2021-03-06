#ifndef ABSIM_ABSIM_H
#define ABSIM_ABSIM_H

#include "event.h"
#include "decaydescriptor.h"
#include "memorymanager.h"
#include "msgservice.h"
#include "backend.h"
#include "clock.h"
#include "sequence.h"
#include "treewriter.h"
#include "configservice.h"
#include "tupleservice.h"

namespace ABSIM {

  struct ABSimConfiguration
  {
    int_t EvtMax = {1000};
    int_t NThreads = {1};
  };

  class ConfigSvc;
  class ABSim
  {
  friend class ConfigSvc;
  friend class TupleSvc;
  private:
    ConfigSvc          cfgsvc_;
    TupleSvc           tupsvc_;
    Sequence           sequence_;
    TreeWriter         writer_;         
    Event*             events_;
    ABSimConfiguration configuration_;
    DecayDescriptor    descriptor_;

    void allocateMemory();

  public:
    ABSim() :
      cfgsvc_( this ),
      tupsvc_( this ),
      writer_("test.root","test.root")
    {};
    ABSim(std::string decay) :
      cfgsvc_( this ),
      tupsvc_( this ),
      writer_("test.root","test.root"),
      descriptor_( decay )
    {}
    ~ABSim() {}

    ABSimConfiguration& operator()() { return configuration_; }

    void run();
    void generate();
    void fillTree();
  };

}  // namespace ABSIM

#endif