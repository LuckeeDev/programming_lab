#include "chain.hpp"

#include "doctest.h"

TEST_CASE("Testing the Chain class") {
  SUBCASE("Testing ordered push back") {
    Hooke hooke{2., 10.};
    Chain chain(hooke);

    ParticleState p1{1., 2., 0.};
    ParticleState p2{1., 0., 0.};
    ParticleState p3{1., 6., 0.};
    chain.push_back(p1);
    chain.push_back(p2);
    chain.push_back(p3);

    CHECK(chain[0].x == p2.x);
    CHECK(chain[1].x == p1.x);
    CHECK(chain[2].x == p3.x);
  }
}