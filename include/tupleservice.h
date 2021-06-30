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
    if ( pos != std::string::npos ) name.replace( pos , 7 , "" );
    return name;
  }

  class ABSim;

  class TupleSvc
  {
  public:
    TupleSvc() = default;
    ~TupleSvc() {}

    template <typename Fn>
    void addEntry(const Fn& fn, int_t index);

    template <typename Fn>
    std::string generateName(const int_t index) const;

    template <typename Fn>
    void addFunction()
    {
      Fn fn;
      info() << quote( fn ) << endmsg;
    }
  };

}  // namespace ABSIM

#endif