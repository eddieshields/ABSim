#include "decay.h"

using namespace ABSIM;

void Decay::setDecay()
{
  std::vector<real_t> masses;
  masses.resize( ndaughters_ );
  for (int_t i = 0; i < ndaughters_; i++) {
    masses[i] = daughters_[i]->mass_(Property::Generated);
    generator_.decProd_[i] = &(daughters_[i]->momentum_(Property::Generated));
  }

  generator_.SetDecay(mother_->momentum_(Property::Generated) , ndaughters_ , masses.data() );
}

void Decay::generateDecay()
{
  bool pass = generator_.UpdateDecay(mother_->momentum_(Property::Generated));
  if ( !pass ) warning() << "Energy not high enough to decay!" << endmsg;
  generator_.Generate();
}