#ifndef TOYGEN_D02KSKK_H
#define TOYGEN_D02KSKK_H

#include "decayalgorithm.h"
#include "configureamplitude.h"
#include "amplitude.h"
#include "msgservice.h"
#include "types.h"
#include "random.h"
#include "properties.h"
#include "msgservice.h"

namespace ABSIM {

  class Decay3Body : public Algorithm
  {
  public:
    Decay3Body(std::string name, int_t index, real_t max, std::string cfgfile) :
      Algorithm(name),
      index_( index ),
      max_( max )
    {
      DalitzModel::ConfigureAmplitude configure( cfgfile );
      amp_ = configure();
    }
    ~Decay3Body() {}
  
    void operator() (Event& ev) final
    {
      auto& decay = ev.decay( index_ );
      real_t mSq12, mSq13;
      real_t pdf = 0;
      while ( pdf < Random::flat( 0 , max_ ) ) {
        ev.reDecay(index_);
        mSq12 = ( decay.daughter(0)->momentum(Property::Generated) + decay.daughter(1)->momentum(Property::Generated) ).M2();
        mSq13 = ( decay.daughter(0)->momentum(Property::Generated) + decay.daughter(2)->momentum(Property::Generated) ).M2();
        pdf = amp_.AdirSq( mSq12 , mSq13 );
      }
    }
  
    DalitzModel::Amplitude amp() { return amp_; }
  private:
    int_t index_;
    real_t max_;
    DalitzModel::Amplitude amp_;
  };

} // namespace ABSIM

#endif