#ifndef ABSIM_FUNCTORS_H
#define ABSIM_FUNCTORS_H

#include "properties.h"
#include "entry.h"
#include "event.h"
#include "particle.h"

namespace ABSIM {

  real_t M2(Particle& particle)
  {
    return particle.momentum(Property::Generated).M2();
  }

}  // namespace ABSIM

#endif