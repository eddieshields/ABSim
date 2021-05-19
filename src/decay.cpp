#include "decay.h"

using namespace ABSIM;

void Decay::generateDecay()
{
  std::vector<real_t> masses;
  masses.resize( ndaughters_ );
  for (int i = 0; i < ndaughters_; i++) {
    masses[i] = daughters_[0]->mass_(Property::Generated);
  }
  generator_.SetDecay(mother_->momentum_(Property::Generated) , ndaughters_ , masses.data() );

  generator_.Generate();
}