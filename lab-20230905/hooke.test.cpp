#include "hooke.hpp"

#include "doctest.h"

TEST_CASE("Testing the Hooke function") {
  Hooke hooke{2., 10.};
  ParticleState p1{1., 0., 0.};
  ParticleState p2{1., 12., 0.};

  CHECK_EQ(hooke(p1, p2), 4.);

  p1 = ParticleState{1., 0., 0.};
  p2 = ParticleState{1., 9., 0.};
  CHECK_EQ(hooke(p1, p2), -2.);

  p1 = ParticleState{1., 5., 0.};
  p2 = ParticleState{1., 15., 0.};
  CHECK_EQ(hooke(p1, p2), 0.);
}