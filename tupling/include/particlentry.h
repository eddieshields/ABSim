#ifndef ABSIM_PARTICLEENTRY_H
#define ABSIM_PARTICLEENTRY_H

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
  class ParticleEntry : public EntryBase
  {
  public:
    const Fn&   fn_;
    const int_t index_;
    T           value_;

    ParticleEntry(const std::string name, const Fn& fn, const int_t index) :
      EntryBase( name , name ),
      fn_( fn ),
      index_( index ),
      value_( 0 )
    {}
    ParticleEntry(const ParticleEntry<Fn,T>& rhs) :
      EntryBase( rhs.name_ , rhs.title_ ),
      fn_( rhs.fn_ ),
      index_( rhs.index_ ),
      value_( rhs.value_ )
    {}
    ~ParticleEntry() {}

    inline void operator()(Event& ev) override
    {
      this->value_ = (*this)( ev.particle( index_ ) );
    }

    inline T operator()(Particle& particle)
    {
      return fn_( particle );
    }

    std::unique_ptr<EntryBase> clone() const override
    {
      return std::make_unique<ParticleEntry<Fn,T>>( *this );
    }

  };

} // namespace ABSIM

#endif