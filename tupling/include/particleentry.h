#ifndef ABSIM_PARTICLEENTRY_H
#define ABSIM_PARTICLEENTRY_H

#include "entry.h"
#include "types.h"

#include <functional>

namespace ABSIM {

  /**
   * @class ParticleEntry
   * 
   * @brief
   * 
   * @details
   * 
   * @author Edward Shields
   * @date 30/06/2021
   */
  template <typename Fn>
  class ParticleEntry : public Entry<std::result_of<Fn(Particle)>::type>
  {
  private:
    const Fn&   fn_;     ///< Functor that is used to calculare the value of the entry from the particle.
    const int_t index_;  ///< Index of particle.

    using T = typename std::result_of<Fn(Particle)>::type;

  public:
    /**
     * Constructor
     * 
     * @param fn Functor
     * @param name Name of entry
     * @param index Index of particle
     */ 
    ParticleEntry(Fn& fn, std::string name,int_t index) :
      Entry<T>( name ),
      fn_( fn ),
      index_( index )
    {}
    ~ParticleEntry() {}

    /**
     * Implementation of virtual operator. This assigns the value of the entry to the address 
     * stored in the TTree.
     * 
     * @param ev Event
     */
    inline void operator()(Event& ev)
    {
      value = fn_( ev.particle(index) );
    }

  };

}  // namespace ABSIM

#endif