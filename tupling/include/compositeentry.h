#ifndef ABSIM_COMPOSITEENTRY_H
#define ABSIM_COMPOSITEENTRY_H

#include "entry.h"

#include <vector>

namespace ABSIM
{

  /**
   * @class CompositeEntry
   * 
   * @brief 
   * 
   * @details
   * 
   * @author Edward Shields
   * @date 30/06/2021
   */
  template <typename Fn>
  class CompositeEntry : public Entry<std::result_of<Fn(Particle)>::type>
  {
  private:
    const Fn&                fn_;       ///< Functor that is used to calculare the value of the entry from the particle.
    const std::vector<int_t> indices_;  ///< Indices of the particles.

    using T = typename std::result_of<Fn(Particle)>::type;

  public:
    /**
     * Constructor
     * 
     * @param fn Functor
     * @param name Name of entry
     * @param indices Indices of the particles
     */
    template<int_t ...I>
    CompositeEntry(Fn& fn, std::string name,I... indices) :
      Entry<T>( name ),
      fn_( fn ),
      indices_( indices... )
    {}
    ~CompositeEntry() {}

    /**
     * Implementation of virtual operator. This assigns the value of the entry to the address 
     * stored in the TTree.
     * 
     * @param ev Event
     */
    inline void operator()(Event& ev)
    {
      //Particle comp;
      //for (const auto& i : indices_) {
      //  comp += ev.particle(i);
      //}
      value = fn_( ev.particle(indices_[0]) );
    }

  };

} // namespace ABSIM

#endif