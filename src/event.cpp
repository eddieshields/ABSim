#include "event.h"

using namespace ABSIM;

Event::Event(const DecayDescriptor& descriptor)
{
  n_ = descriptor.nparticles();
  particles_ = new Particle[n_];
  decays_ = new Decay[descriptor.ndecays()];

  int i = 0;

  for (auto name : descriptor.particles()) {
    particles_[i] = descriptor.info()[name];
    ++i;
  }

  // Set Momentum of head particle.
  particles_[i].momentum_(Property::Generated) = FourVector(0,0,0,Beam::Energy + particles_[0].mass_(Property::Generated));

  i = 0;
  for (auto decay : descriptor.decays()) {
      decays_[i].mother_ = particles_ + decay->index( decay->particles().front() );
      for (int j = 1; j < decay->size(); j++) {
        decays_[i].daughters_[j-1] = particles_ + decay->index( decay->particles()[j] );
      }
      decays_[i].setDecay();
      ++i;
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
  for (int i = 0; i < n_; i++) {
    decays_[i].generateDecay();
  }
}
