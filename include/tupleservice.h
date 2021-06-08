#ifndef ABSIM_TUPLESERVICE_H
#define ABSIM_TUPLESERVICE_H

#include "treewriter.h"
#include "entry.h"
#include "types.h"
#include "msgservice.h"

#include <cxxabi.h>

#include <string>

namespace ABSIM {

  template <typename Fn>
  std::string quote(const Fn& fn)
  {
    int status;
    const char* demangled = abi::__cxa_demangle(typeid(fn).name(),0,0,&status);
    std::string name(demangled);
    delete demangled;
    int pos = name.find("ABSIM::");
    return name.replace( pos , 7 , "" );
  }

  class ABSim;

  class TupleSvc
  {
  private:
    const ABSim* target_;

  public:
    TupleSvc(const ABSim* target) :
      target_( target )
    {}
    ~TupleSvc() {}

    template <typename Fn>
    void addEntry(std::string name, const Fn& fn, int_t index);

    template <typename Fn>
    void addFunction()
    {
      Fn fn;
      info() << quote( fn ) << endmsg;
    }
  };

}  // namespace ABSIM

#endif