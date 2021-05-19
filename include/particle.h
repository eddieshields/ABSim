#ifndef ABSIM_PARTICLE_H
#define ABSIM_PARTICLE_H

#include "types.h"
#include "particleproperty.h"
#include "vertex.h"
#include "fourvector.h"
#include "memorymanager.h"
#include "particlestore.h"

#include <string>
#include <iostream>

namespace ABSIM {

  class Particle
  {
  friend class Decay;
  private:
    ParticleProperty<FourVector> momentum_;
    ParticleProperty<Vertex>     org_vertex_;
    ParticleProperty<Vertex>     end_vertex_;
    std::string                  name_;
    ParticleProperty<real_t>     mass_;
    ParticleProperty<real_t>     time_;
    ParticleProperty<int>        pid_;
    ParticleProperty<int>        q_;

  public:
    static std::string NAME() { return "Particle"; }
    Particle() = default;
    Particle(std::string name, real_t mass, real_t time, int pid, int q) :
      momentum_(),
      org_vertex_(),
      end_vertex_(),
      name_( name ),
      mass_( mass),
      time_( time ),
      pid_( pid ),
      q_( q )
    {}
    Particle(const Particle& rhs) :
      momentum_( rhs.momentum_ ),
      org_vertex_( rhs.org_vertex_ ),
      end_vertex_( rhs.end_vertex_ ),
      name_( rhs.name_ ),
      mass_( rhs.mass_ ),
      time_( rhs.time_ ),
      pid_( rhs.pid_ ),
      q_( rhs.q_ )
    {}
    Particle(const BasicParticleInfo& info) :
      momentum_(),
      org_vertex_(),
      end_vertex_(),
      name_( info.name ),
      mass_( info.mass ),
      time_( info.time ),
      pid_( info.pid ),
      q_( info.q )
    {}
    ~Particle() {}

    Particle& operator=(const Particle& rhs)
    {
      momentum_ = rhs.momentum_;
      org_vertex_ = rhs.org_vertex_;
      end_vertex_ = rhs.end_vertex_;
      name_ = rhs.name_;
      mass_ = rhs.mass_;
      time_ = rhs.time_;
      pid_ = rhs.pid_;
      q_ = rhs.q_;
      return *this;
    }
    Particle& operator=(const BasicParticleInfo& rhs)
    {
      name_ = rhs.name;
      mass_ = rhs.mass;
      //time_ = rhs.time;
      //pid_ = rhs.pid;
      //q_ = rhs.q;
      return *this;
    }

    const std::string name() const { return name_; };


    real_t FD() { return end_vertex_.generated() - org_vertex_.generated(); }

    void* operator new (size_t size)
    {
      return MemoryManager<Particle>::allocate( size );
    }

    void* operator new[] (size_t size)
    {
      return MemoryManager<Particle>::allocate( size );
    }
    
    void operator delete (void* deleted)
    {
      MemoryManager<Particle>::free( deleted );
    }

  };

} // namespace ABSIM

#endif