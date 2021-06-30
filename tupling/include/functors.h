#ifndef ABSIM_FUNCTORS_H
#define ABSIM_FUNCTORS_H

#include "properties.h"
#include "entry.h"
#include "event.h"
#include "particle.h"

using namespace ABSIM;

struct Px { inline real_t operator()(Particle& particle) { return particle.momentum(Property::Generated).Px(); } };

struct Py { inline real_t operator()(Particle& particle) { return particle.momentum(Property::Generated).Py(); } };

struct Pz { inline real_t operator()(Particle& particle) { return particle.momentum(Property::Generated).Pz(); } };

struct E { inline real_t operator()(Particle& particle) { return particle.momentum(Property::Generated).E(); } };

struct P { inline real_t operator()(Particle& particle) { return particle.momentum(Property::Generated).P(); } };

struct Pt { inline real_t operator()(Particle& particle) { return particle.momentum(Property::Generated).Pt(); } };

struct M { inline real_t operator()(Particle& particle) { return particle.momentum(Property::Generated).M(); } };

struct M2 { inline real_t operator()(Particle& particle) { return particle.momentum(Property::Generated).M2(); } };

struct T { inline real_t operator()(Particle& particle) { return particle.time(Property::Generated); } };

struct vtxX { inline real_t operator()(Particle& particle) { return particle.end_vertex(Property::Generated).X(); } };

struct vtxY { inline real_t operator()(Particle& particle) { return particle.end_vertex(Property::Generated).Y(); } };

struct vtxZ { inline real_t operator()(Particle& particle) { return particle.end_vertex(Property::Generated).X(); } };

struct orgX { inline real_t operator()(Particle& particle) { return particle.org_vertex(Property::Generated).X(); } };

struct orgY { inline real_t operator()(Particle& particle) { return particle.org_vertex(Property::Generated).Y(); } };

struct orgZ { inline real_t operator()(Particle& particle) { return particle.org_vertex(Property::Generated).Z(); } };

struct pid { inline real_t operator()(Particle& particle) { return particle.pid(Property::Generated); } };

struct q { inline real_t operator()(Particle& particle) { return particle.q(Property::Generated); } };

#endif 