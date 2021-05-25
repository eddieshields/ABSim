#include "decay.h"

using namespace ABSIM;

void Decay::setDecay()
{
  std::vector<real_t> masses;
  masses.resize( ndaughters_ );
  for (int i = 0; i < ndaughters_; i++) {
    masses[i] = daughters_[i]->mass_(Property::Generated);
    generator_.decProd_[i] = &(daughters_[i]->momentum_(Property::Generated));
  }

  bool pass = generator_.SetDecay(mother_->momentum_(Property::Generated) , ndaughters_ , masses.data() );
  ABSIM_INFO( pass );
}

void Decay::generateDecay()
{
  //generator_.UpdateDecay(mother_->momentum_(Property::Generated));
  //ABSIM_INFO(mother_->momentum_(Property::Generated).M2());
  setDecay();
  ABSIM_INFO( generator_.Generate() );
}