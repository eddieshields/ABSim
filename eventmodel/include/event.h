#ifndef ABSIM_EVENT_H
#define ABSIM_EVENT_H

#include "particle.h"
#include "decay.h"
#include "beam.h"
#include "decaydescriptor.h"
#include "msgservice.h"

#include <vector>

namespace ABSIM {

  /**
   * @class Event
   * 
   * @brief Event model to be generated.
   * 
   * @details
   * 
   * @author Edward Shields
   * @date 30/06/2021
   */
  class Event
  {
  private:
    int_t     n_;           ///< Number of particles in the event.
    int_t     ndecays_;     ///< Number of decays in the event.
    Particle* particles_;   ///< Array of particles in the event.
    Decay*    decays_;      ///< Array of decays in the event.

  public:
    static std::string NAME() { return "Event"; }

    /**
     * Constructor.
     */
    Event() = default;

    /**
     * Constructor
     * 
     * @param descriptor Decay descriptor
     */
    Event(const DecayDescriptor& descriptor);
    ~Event() {}

    /**
     * Reset the whole event.
     */
    void reset();

    /**
     * Generate the full event.
     */
    void generate();

    /**
     * Redecay a decay and all sub-decays coming from it.
     * 
     * @param i Index of decay to redecay.
     * 
     * By decaying decay 0 the whole event will be regenerated.
     */
    void reDecay(const int_t& i);

    // Getters.
    /**
     * Return array of particles.
     */
    Particle* particles() { return particles_; }

    /**
     * Return a particle by it's index.
     * 
     * @param i Index of particle
     */
    Particle& particle(const int_t i)
    {
      if ( i > n_ ) warning() << "Bad index " << i << leave;
      return particles_[i];
    }

    /**
     * Return array of decays.
     */
    Decay*    decays()    { return decays_; }
    
    /**
     * Return a decay by it's index.
     * 
     * @param i Index of decay.
     */
    Decay&    decay(const int_t i)
    {
      if ( i > ndecays_ ) warning() << "Bad index " << i << leave;
      return decays_[i];
    }
  };

} // namespace ABSIM

#endif