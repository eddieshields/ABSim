#ifndef ABSIM_DECAYDESCRIPTOR_H
#define ABSIM_DECAYDESCRIPTOR_H

#include "particlestore.h"
#include "msgservice.h"

#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <unordered_map>

namespace ABSIM {

  struct SubDecayDescriptor
  {
    SubDecayDescriptor*                       from_;
    std::vector<std::string>                  particles_;
    std::map<std::string,SubDecayDescriptor*> decays_;

    friend std::ostream& operator<<(std::ostream& os, const SubDecayDescriptor& subdecay)
    {
      os << subdecay.particles_.front() << " => ";
      for (unsigned int i = 0; i < subdecay.particles_.size(); ++i) {
        std::string part = subdecay.particles_[i];
        auto it = subdecay.decays_.find( part );
        if ( it->second != nullptr ) os << *(it->second);
        else os << subdecay.particles_[i] << " ";
      }
      return os;
    }
  };

  class DecayDescriptor
  {
  private:
    std::string                                       decay_;
    std::string                                       head_;
    std::vector<std::string>                          particles_;
    std::vector<SubDecayDescriptor*>                  subdecays_;
    std::unordered_map<std::string,BasicParticleInfo> infos_;

    // Decode Descriptor.
    void decodeDecay(std::string decay);
    bool beginDecay(std::string entry);
    bool endDecay(std::string entry);
    bool isDecaySign(std::string entry);
    void getInfo(std::string entry);

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

    int nparticles() const { return particles_.size(); }
    int ndecays()    const { return subdecays_.size(); }
    int maxparticles() const;

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