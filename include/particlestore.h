#ifndef ABSIM_PARTICLESTORE_H
#define ABSIM_PARTICLESTORE_H

#include "msgservice.h"
#include "types.h"

#include "TDatabasePDG.h"
#include "TParticlePDG.h"

#include <string>
#include <map>

namespace ABSIM {

  struct BasicParticleInfo
  {
    std::string name;
    real_t      mass;
    real_t      time;
    int_t         pid;
    int_t         q;
    bool        stable;
    int_t decay_index;
  };

  class ParticleStore
  {
  private:
    static TDatabasePDG                            pdg_;

  public:
    static BasicParticleInfo getParticle(std::string name)
    {
      TParticlePDG* pdg_particle = pdg_.GetParticle(name.c_str());
      if ( pdg_particle == nullptr ) fatal() << "Particle " << name << " is not recognised!" << leave;

      BasicParticleInfo particle;
      particle.name = name;
      particle.mass = pdg_particle->Mass();
      particle.time = pdg_particle->Lifetime();
      particle.pid  = pdg_particle->PdgCode();
      particle.q    = pdg_particle->Charge();

      return particle;
    }
  };

} // namsespace ABSIM

#endif