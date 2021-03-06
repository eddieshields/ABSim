#ifndef ABSIM_PARTICLE_H
#define ABSIM_PARTICLE_H

#include "types.h"
#include "particleproperty.h"
#include "vertex.h"
#include "fourvector.h"
#include "particlestore.h"

#include <string>
#include <iostream>

namespace ABSIM {

  class Particle
  {
  friend class Decay;
  friend class Event;
  private:
    ParticleProperty<FourVector> momentum_;
    ParticleProperty<Vertex>     org_vertex_;
    ParticleProperty<Vertex>     end_vertex_;
    std::string                  name_;
    ParticleProperty<real_t>     mass_;
    ParticleProperty<real_t>     time_;
    ParticleProperty<int_t>      pid_;
    ParticleProperty<int_t>      q_;

    bool                         stable_;
    int_t                        decay_index_;

  public:
    static std::string NAME() { return "Particle"; }
    Particle() = default;
    Particle(std::string name, real_t mass, real_t time, int_t pid, int_t q) :
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
      q_( rhs.q_ ),
      stable_( rhs.stable_ ),
      decay_index_( rhs.decay_index_ )
    {}
    Particle(const BasicParticleInfo& info) :
      momentum_(),
      org_vertex_(),
      end_vertex_(),
      name_( info.name ),
      mass_( info.mass ),
      time_( info.time ),
      pid_( info.pid ),
      q_( info.q ),
      stable_( info.stable ),
      decay_index_( info.decay_index )
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
      stable_ = rhs.stable_;
      decay_index_ = rhs.decay_index_;
      return *this;
    }
    Particle& operator=(const BasicParticleInfo& rhs)
    {
      name_ = rhs.name;
      mass_ = rhs.mass;
      time_ = rhs.time;
      pid_ = rhs.pid;
      q_ = rhs.q;
      stable_ = rhs.stable;
      decay_index_ = rhs.decay_index;
      return *this;
    }

    const std::string name() const { return name_; };

    inline void construct(const BasicParticleInfo& info)
    {
      name_ = info.name;
      mass_ = info.mass;
      time_ = info.time;
      pid_ = info.pid;
      q_ = info.q;
      stable_ = info.stable;
      decay_index_ = info.decay_index;
    }

    void reset()
    {
      momentum_ = FourVector();
      org_vertex_ = Vertex();
      end_vertex_ = Vertex();
    }

    inline ParticleProperty<FourVector>& momentum()   { return momentum_; }
    inline ParticleProperty<Vertex>&     org_vertex() { return org_vertex_; }
    inline ParticleProperty<Vertex>&     end_vertex() { return end_vertex_; }
    inline std::string&                  name()       { return name_; }
    inline ParticleProperty<real_t>&     mass()       { return mass_; }
    inline ParticleProperty<real_t>&     time()       { return time_; }
    inline ParticleProperty<int_t>&      pid()        { return pid_; }
    inline ParticleProperty<int_t>&      q()          { return q_; }

    inline FourVector& momentum(Property::Type type)   { return momentum_(type); }
    inline Vertex&     org_vertex(Property::Type type) { return org_vertex_(type); }
    inline Vertex&     end_vertex(Property::Type type) { return end_vertex_(type); }
    inline real_t&     mass(Property::Type type)       { return mass_(type); }
    inline real_t&     time(Property::Type type)       { return time_(type); }
    inline int_t&      pid(Property::Type type)        { return pid_(type); }
    inline int_t&      q(Property::Type type)          { return q_(type); }


    real_t FD() { return end_vertex_.generated() - org_vertex_.generated(); }

  };

} // namespace ABSIM

#endif