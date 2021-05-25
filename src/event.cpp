#include "event.h"

using namespace ABSIM;

Event::Event(const DecayDescriptor& descriptor)
{
  n_ = descriptor.nparticles();
  ndecays_ = descriptor.ndecays();
  particles_ = new Particle[n_];
  decays_ = new Decay[ndecays_];

  int i = 0;
  for (i = 0; i < n_; i++) {
    particles_[i].construct( descriptor.particles()[i] );
  }

  // Set Momentum of head particle.
  particles_[0].momentum_(Property::Generated) = FourVector(0,0,0,particles_[0].mass_(Property::Generated));

  for (i = 0; i < ndecays_; i++) {
    decays_[i].construct( particles_ , descriptor.decays()[i] );
  }
}

void Event::reset()
{
  for (int i = 0; i < n_; i++) {
    particles_[i].reset();
  }
}

void Event::generate()
{
  for (int i = 0; i < ndecays_; i++) {
    decays_[i].generateDecay();
  }
}
