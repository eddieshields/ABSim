#include "catch.hpp"

#include "particleproperty.h"

using namespace ABSIM;

TEST_CASE( "Test ParticleProperty", "[ParticleProperty]") {
  ParticleProperty<real_t> p1;
  ParticleProperty<real_t> p2;

  ParticleProperty<int> p3;
  ParticleProperty<int> p4;

  ParticleProperty<complex_t> p5;
  ParticleProperty<complex_t> p6;
}