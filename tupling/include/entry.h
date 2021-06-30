#ifndef ABSIM_ENTRY_H
#define ABSIM_ENTRY_H

#include "entrybase.h"
#include "properties.h"
#include "types.h"
#include "event.h"
#include "functors.h"

#include <string>
#include <functional>
#include <memory>

namespace ABSIM {

  template <typename Fn, typename T>
  class Entry : public EntryBase
  {
  public:
    Fn fn_;
    T  value_;

    Entry(const std::string name, const Fn& fn) :
      EntryBase( name , get_title<T>(name) ),
      fn_( fn ),
      value_( 0 )
    {}
    Entry(const Entry<Fn,T>& rhs) :
      EntryBase( rhs.name_ , rhs.title_ ),
      fn_( rhs.fn_ ),
      value_( rhs.value_ )
    {}
    ~Entry() {}

    inline void operator()(Event& ev) override
    {
      this->value_ = fn_( ev.particle(0) );
    }

  };

} // namespace ABSIM

#endif