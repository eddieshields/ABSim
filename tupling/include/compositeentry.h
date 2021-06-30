#ifndef ABSIM_COMPOSITEENTRY_H
#define ABSIM_COMPOSITEENTRY_H

#include "types.h"
#include "entrybase.h"

namespace ABSIM {

  template <typename Fn, typename T>
  class CompositeEntry : public EntryBase
  {
  public:
    Fn    fn_;
    const int_t index1_;
    const int_t index2_;
    T           value_;

    CompositeEntry(const std::string name, const Fn& fn, const int_t index1, const int_t index2) :
      EntryBase( name , get_title<T>(name) ),
      fn_( fn ),
      index1_( index1 ),
      index2_( index2 ),
      value_( 0 )
    {}
    CompositeEntry(const CompositeEntry<Fn,T>& rhs) :
      EntryBase( rhs.name_ , rhs.title_ ),
      fn_( rhs.fn_ ),
      index1_( rhs.index1_ ),
      index2_( rhs.index2_ ),
      value_( rhs.value_ )
    {}
    ~CompositeEntry() {}

    inline void operator()(Event& ev) override
    {
      this->value_ = (*this)( ev.particle( index1_ ) + ev.particle( index2_ ) );
    }

    inline T operator()(Particle& particle)
    {
      return fn_( particle );
    }

  };

}  // namespace ABSIM

#endif