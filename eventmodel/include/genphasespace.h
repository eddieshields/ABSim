#ifndef ABSIM_GENPHASESPACE_H
#define ABSIM_GENPHASESPACE_H

#include "types.h"
#include "fourvector.h"
#include "msgservice.h"
#include "particle.h"
#include "random.h"

#include <math.h>

namespace ABSIM {

  /**
   * @class GenPhaseSpace
   * 
   * @brief Implementation of ROOT's TGenPhaseSpace.
   * 
   * @details Implementation of ROOT's TGenPhaseSpace algorithm (https://root.cern.ch/doc/master/classTGenPhaseSpace.html)
   * base on the GENBOD function (W515 from CERNLIB) using the Raubold and Lynch method F. James, Monte Carlo Phase Space, 
   * CERN 68-15 (1968).
   * Generated a decay from a mother to N daughters according to a phase-space distrribution.
   * 
   * @author Rene Brun
   * @author Valerio Filippini
   * @author Edward Shields
   * @date 30/06/2021
   */
  class GenPhaseSpace
  {
  friend class Decay;
  private: 
    int_t n_;                   ///< Number of particles to be decayed.
    real_t mass_[18];           ///< Array of masses of daughter particles.
    real_t beta_[3];            ///< Betas of decaying particles.
    real_t teCmTm_;             ///< Center of Mass energyminus total mass.
    real_t pM_;                 ///< Total mass.
    real_t wtMax_;              ///< Maximum weigth.
    FourVector* decProd_[18];   ///< Linematics of the generated particles.

    /**
     * PDK function.
     */
    inline real_t pdk_(real_t a, real_t b, real_t c) const;

  public:
  /**
   * Constructor.
   */
    GenPhaseSpace() :
      n_( 0 ),
      mass_(),
      beta_(),
      teCmTm_( 0. ),
      wtMax_( 0. )
    {}

    /**
     * Copy constructor.
     */
    GenPhaseSpace(const GenPhaseSpace& gen);

    ~GenPhaseSpace() {}

    /**
     * Move operator.
     */
    GenPhaseSpace& operator=(const GenPhaseSpace& gen);

    /**
     * Set the decay.
     * 
     * @param p Four momentum vector of mother
     * @param n Number of decay products
     * @param mass Array of decay product masses
     */
    bool SetDecay(FourVector& p, int_t n, const real_t* mass);

    /**
     * Update the decay to redecay.
     * 
     * @param p Four momentum vector of mother
     */
    bool UpdateDecay(FourVector& p);

    /**
     * Generate a randim final state.
     * Return the weight of the current decay.
     */
    real_t Generate();

    /**
     * Get the Four momentum vector of a decay product by it's index.
     */
    FourVector* GetDecay(int_t n);

    /**
     * Get number of decay products.
     */
    inline int_t GetN() const { return n_; }

    /**
     * Get maximum weight.
     */
    inline real_t GetWtMax() const { return wtMax_; }
  };

  inline real_t GenPhaseSpace::pdk_(real_t a, real_t b, real_t c) const
  {
    real_t x = (a-b-c)*(a+b+c)*(a-b+c)*(a+b-c);
    x = std::sqrt(x) / 2*a;
    return x;
  }

} // namespace ABSIM

#endif