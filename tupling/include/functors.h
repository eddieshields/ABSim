#ifndef ABSIM_FUNCTORS_H
#define ABSIM_FUNCTORS_H

#include "particle.h"
#include "properties.h"

inline real_t Px(Particle& particle) { return particle.momentum(Property::Generated).Px(); }

inline real_t Py(Particle& particle) { return particle.momentum(Property::Generated).Py(); }

inline real_t Pz(Particle& particle) { return particle.momentum(Property::Generated).Pz(); }

inline real_t E(Particle& particle) { return particle.momentum(Property::Generated).E(); }

inline real_t P(Particle& particle) { return particle.momentum(Property::Generated).P(); }

inline real_t Pt(Particle& particle) { return particle.momentum(Property::Generated).Pt(); }

inline real_t M(Particle& particle) { return particle.momentum(Property::Generated).M(); }

inline real_t M2(Particle& particle) { return particle.momentum(Property::Generated).M2(); }

inline real_t T(Particle& particle) { return particle.time(Property::Generated); }

inline real_t vtxX(Particle& particle) { return particle.end_vertex(Property::Generated).X(); }

inline real_t vtxY(Particle& particle) { return particle.end_vertex(Property::Generated).Y(); }

inline real_t vtxZ(Particle& particle) { return particle.end_vertex(Property::Generated).X(); }

inline real_t orgX(Particle& particle) { return particle.org_vertex(Property::Generated).X(); }

inline real_t orgY(Particle& particle) { return particle.org_vertex(Property::Generated).Y(); }

inline real_t orgZ(Particle& particle) { return particle.org_vertex(Property::Generated).Z(); }

inline real_t pid(Particle& particle) { return particle.pid(Property::Generated); }

inline real_t q(Particle& particle) { return particle.q(Property::Generated); }

#endif