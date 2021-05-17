#ifndef ABSIM_PARTICLE_H
#define ABSIM_PARTICLE_H

#include "types.h"
#include "particleproperty.h"
#include "vertex.h"

#include <string>

namespace ABSIM {

  class Particle
  {
  private:
    ParticleProperty<Vertex> org_vertex_;
    ParticleProperty<Vertex> end_vertex_;
    const std::string        name_;
    ParticleProperty<real_t> mass_;
    ParticleProperty<real_t> time_;
    ParticleProperty<int>    pid_;
    ParticleProperty<int>    q_;

  public:
    Particle() :
      name_( "default_particle" )
    {}
    ~Particle() {}


    //real_t FD() { return end_vertex_.generated() - org_vertex_.generated(); }
  };

} // namespace ABSIM

#endif