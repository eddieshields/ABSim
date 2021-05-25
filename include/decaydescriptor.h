#ifndef ABSIM_DECAYDESCRIPTOR_H
#define ABSIM_DECAYDESCRIPTOR_H

#include "particlestore.h"
#include "msgservice.h"

#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <unordered_map>
#include <algorithm>

namespace ABSIM {

  struct SubDecayDescriptor
  {
    SubDecayDescriptor*                       from_;
    std::vector<std::string>                  particles_;
    std::vector<int>                          indices_;
    std::map<int,SubDecayDescriptor*>         decays_;

    void addParticle(std::string name, int index)
    {
      particles_.push_back( name );
      indices_.push_back( index );
    }
    void addDecay(int index, SubDecayDescriptor* decay)
    {
      decays_.insert( std::pair<int,SubDecayDescriptor*>( index , decay ) );
    }
    inline int                       size() const             { return static_cast<int>(particles_.size()); }
    inline std::vector<std::string>& particles()              { return particles_; }

    friend std::ostream& operator<<(std::ostream& os, const SubDecayDescriptor& subdecay)
    {
      os << subdecay.particles_.front() << " => ";
      for (unsigned int i = 0; i < subdecay.particles_.size(); ++i) {
        auto it = subdecay.decays_.find( i );
        if ( it->second != nullptr ) os << *(it->second);
        else os << subdecay.particles_[i] << " ";
      }
      return os;
    }
  };

  struct DecayInfo
  {
    int              ndaughters;
    int              mother;
    std::vector<int> daughters;
  };

  class DecayDescriptor
  {
  private:
    std::string                                       decay_;
    std::string                                       head_;
    std::vector<std::string>                          particles_;
    std::vector<SubDecayDescriptor*>                  subdecays_;

    std::vector<BasicParticleInfo>                     particle_info_;
    std::vector<DecayInfo>                             decay_info_;

    // Decode Descriptor.
    void decodeDecay(std::string decay);
    bool beginDecay(std::string entry);
    bool endDecay(std::string entry);
    bool isDecaySign(std::string entry);
    void getParticleInfo(std::string entry);
    int currentIndex() { return particles_.size() - 1; }

    // Print Descriptor.
    std::string print_subdecay(std::string& out, SubDecayDescriptor* subdecay) const;
    std::string decay_string() const;

  public:
    DecayDescriptor() = default;
    DecayDescriptor(std::string decay) :
      decay_( decay )
    {
      decodeDecay(decay_);
    }
    ~DecayDescriptor() {}

    inline std::vector<BasicParticleInfo>                    particles() const { return particle_info_; }
    inline std::vector<DecayInfo>                            decays()    const { return decay_info_; }

    inline int nparticles() const { return particles_.size(); }
    inline int ndecays()    const { return subdecays_.size(); }

    void Print() const;

    // I/O operators.
    friend std::ostream& operator<<(std::ostream& os, const DecayDescriptor decay)
    {
      os << decay.decay_string();
      return os;
    };

    friend std::istream& operator>>(std::istream& is, DecayDescriptor& decay)
    {
      std::string decay_string;
      is >> decay_string;
      decay.decay_ = decay_string;
      decay.decodeDecay( decay_string );
      return is;
    }

  };

} // namesapce ABSIM

#endif