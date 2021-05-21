#ifndef ABSIM_GENPHASESPACE_H
#define ABSIM_GENPHASESPACE_H

#include "types.h"
#include "fourvector.h"
#include "msgservice.h"
#include "particle.h"

#include <math.h>

namespace ABSIM {

  class GenPhaseSpace
  {
  friend class Decay;
  private: 
    int n_;
    real_t mass_[18];
    real_t beta_[3];
    real_t teCmTm_;
    real_t pM_;
    real_t wtMax_;
    FourVector* decProd_[18];

    inline real_t pdk_(real_t a, real_t b, real_t c) const;

  public:
    GenPhaseSpace() :
      n_( 0 ),
      mass_(),
      beta_(),
      teCmTm_( 0. ),
      wtMax_( 0. )
    {}
    GenPhaseSpace(const GenPhaseSpace& gen);
    ~GenPhaseSpace() {}
    GenPhaseSpace& operator=(const GenPhaseSpace& gen);

    bool SetDecay(FourVector& p, int n, const real_t* mass);
    bool UpdateDecay(FourVector& p);
    real_t Generate();
    FourVector* GetDecay(int n);

    inline int GetN() const { return n_; }
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