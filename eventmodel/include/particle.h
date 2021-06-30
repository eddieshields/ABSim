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

  /**
   * @class Particle
   * 
   * @brief
   * 
   * @details
   * 
   * @author Edward Shields
   * @date 30/06/2021
   */
  class Particle
  {
  friend class Decay;
  friend class Event;
  private:
    ParticleProperty<FourVector> momentum_;    ///< Four momentum.
    ParticleProperty<Vertex>     org_vertex_;  ///< Origin vertex.
    ParticleProperty<Vertex>     end_vertex_;  ///< Decay vertex.
    std::string                  name_;        ///< PDG name.
    ParticleProperty<real_t>     mass_;        ///< Mass.
    ParticleProperty<real_t>     time_;        ///< Decay time.
    ParticleProperty<int_t>      pid_;         ///< PDG PID code.
    ParticleProperty<int_t>      q_;           ///< Charge.

    bool                         stable_;      ///< Is stable.
    int_t                        decay_index_; ///< Index of particle in event.

  public:
    static std::string NAME() { return "Particle"; }
    /**
     * Constructor.
     */
    Particle() = default;

    /**
     * Constructor
     * 
     * @param name PDG name
     * @param mass Mass
     * @param time Decay time
     * @param pid PDG PID code
     * @param q Charge
     */
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

    /**
     * Copy constructor.
     */
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

    /**
     * Constructor
     * 
     * @param info BasicParticleInfo container
     */
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

    /**
     * Move operator
     */
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

    /**
     * Create particle from BasicParticleInfo.
     */
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

    /**
     * Returns name of particle.
     */
    const std::string name() const { return name_; };

    /**
     * Construct particle from BasicParticleInfo.
     */
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

    /**
     * Reset generated variables.
     */
    void reset()
    {
      momentum_ = FourVector();
      org_vertex_ = Vertex();
      end_vertex_ = Vertex();
    }

    inline ParticleProperty<FourVector>& momentum()   { return momentum_; }        //!< Return Four momentum
    inline ParticleProperty<Vertex>&     org_vertex() { return org_vertex_; }      //!< Return Origin vertex
    inline ParticleProperty<Vertex>&     end_vertex() { return end_vertex_; }      //!< Return Decay vertex        
    inline ParticleProperty<real_t>&     mass()       { return mass_; }            //!< Return mass
    inline ParticleProperty<real_t>&     time()       { return time_; }            //!< Return decay time
    inline ParticleProperty<int_t>&      pid()        { return pid_; }             //!< Return PID
    inline ParticleProperty<int_t>&      q()          { return q_; }               //!< Return charge

    inline FourVector& momentum(Property::Type type)   { return momentum_(type); }
    inline Vertex&     org_vertex(Property::Type type) { return org_vertex_(type); }
    inline Vertex&     end_vertex(Property::Type type) { return end_vertex_(type); }
    inline real_t&     mass(Property::Type type)       { return mass_(type); }
    inline real_t&     time(Property::Type type)       { return time_(type); }
    inline int_t&      pid(Property::Type type)        { return pid_(type); }
    inline int_t&      q(Property::Type type)          { return q_(type); }


    /**
     * Calculates flight distance of the particle.
     */
    real_t FD() { return end_vertex_.generated() - org_vertex_.generated(); }

  };

} // namespace ABSIM

#endif