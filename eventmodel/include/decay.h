#ifndef ABSIM_DECAY_H
#define ABSIM_DECAY_H

#include "particle.h"
#include "decaydescriptor.h"
#include "genphasespace.h"

#include <array>
#include <vector>

namespace ABSIM {

  const int_t MAXP_ = 18;

  /**
   * @class Decay
   * 
   * @brief Class to represent the decay of a particle int_to N other particles.
   * 
   * @details
   * 
   * @author Edward Shields
   * @date 11/05/2021
   */
  class Decay {
  friend class Event;
  private:
    Particle* mother_;                  ///< Pointer to mother particle
    Particle* daughters_[MAXP_];        ///< Array of pointers to daughter particles.
    int_t     ndaughters_;              ///< Number of daughters.

    GenPhaseSpace          generator_;  ///< Phasespace generator.

  public:
    static std::string NAME() { return "Decay"; }

    /**
     * Constructor.
     */
    Decay() {}
    ~Decay() {}

    /**
     * Construct the decay.
     * 
     * @param particles Array of particles from Event
     * @param info Info about decay
     */
    void construct(Particle* particles, const DecayInfo& info);

    /**
     * Set decay so the generator is pointing to the correct particles.
     */
    void setDecay();

    /**
     * Generate a decay with a phasespace distribution.
     */
    void generateDecay();

    /**
     * Return pointer to mother particle.
     */
    Particle* mother() { return mother_; }

    /**
     * Return pointer to daughter particle by index.
     * 
     * @param i Index of particle
     */
    Particle* daughter(const int_t& i)
    { 
      if ( i > ndaughters_ ) warning() << "Bad index " << i << endmsg;
      return daughters_[i];
    } 
  };

} // namespace ABSIM

#endif