#include "event.h"

using namespace ABSIM;

Event::Event(const DecayDescriptor& descriptor)
{
  particles_ = new Particle[descriptor.nparticles()];
  decays_ = new Decay[descriptor.ndecays()];

  int i = 0;

  for (auto name : descriptor.particles()) {
    particles_[i] = descriptor.info()[name];
    ++i;
  }

  i = 0;
  for (auto decay : descriptor.decays()) {
      decays_[i].mother_ = particles_ + decay->index( decay->particles().front() );
      for (int j = 1; j < decay->particles().size(); j++) {
        decays_[i].daughters_[j-1] = particles_ + decay->index( decay->particles()[j] );
      }
      ++i;
  }
}
