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
 info() << pass << endmsg;
}

void Decay::generateDecay()
{
  //generator_.UpdateDecay(mother_->momentum_(Property::Generated));
  //info() << mother_->momentum_(Property::Generated).M2() << endmsg;
  setDecay();
  info() <<  generator_.Generate() << endmsg;
}