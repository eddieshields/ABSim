#ifndef ABSIM_CONFIGSERVICE_H
#define ABSIM_CONFIGSERVICE_H

#include "linkedlist.h"
#include "algorithm.h"
#include "entrybase.h"
#include "sequence.h"

namespace ABSIM {

  class ConfigSvc
  {
  private:
    Sequence algorithms_;
    LinkedList<EntryBase> entries_;

  public:
    ConfigSvc() = default;
    ~ConfigSvc() {}

    template<typename Arg, typename... Args>
    void addAlgorithms(const Arg& alg, Args... algs);

    template<typename Arg>
    void addAlgorithms(const Arg& alg);
  };

}  // namespace ABSIM

#endif