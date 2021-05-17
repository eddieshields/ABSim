#ifndef ABSIM_DECAY_H
#define ABSIM_DECAY_H

#include "particle.h"

#include <array>
#include <vector>

namespace ABSIM {

  /**
   * Decay
   * 
   * Class to represent the decay of a particle into N other particles.
   * 
   * @author Edward Shields
   * @date 11/05/2021
   */
  class Decay {
  private:
    //Particle*              head_;
    //std::vector<Particle*> daughters_;

    //const int    nt_;
    //real_t       mass_[18];
    //real_t       teCmTm_;
    //real_t       wtMax_;

  public:
    //Decay(Particle* head, std::vector<Particle*> daughters) :
    //  head_( head ),
    //  daughters_( daughters ),
    //  nt_( daughters_.size() )
    //{}
    Decay() {}
    ~Decay() {}

    void generate();

  private:
    inline static real_t q(const real_t& m, const real_t& m1, const real_t& m2) { return 0.5 * sqrt( m*m - 2*m1*m1 - 2*m2*m2 + (m1*m1-m2*m2)*(m1*m1-m2*m2)/(m*m) ); }
  };

} // namespace ABSIM

#endif