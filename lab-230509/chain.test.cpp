#include "chain.hpp"

#include "doctest.h"

TEST_CASE("Testing the Chain class") {
  Hooke hooke{2., 10.};
  Chain chain(hooke);

  SUBCASE("Testing ordered push back") {
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

  SUBCASE("Testing evolve method with two particles") {
    ParticleState p1{1., 0., 0.};
    ParticleState p2{1., 12., 0.};
    chain.push_back(p1);
    chain.push_back(p2);

    chain.evolve(1.0);

    CHECK(chain[0].m == 1.);
    CHECK(chain[0].x == 2.);
    CHECK(chain[0].v == 4.);

    CHECK(chain[1].m == 1.);
    CHECK(chain[1].x == 10.);
    CHECK(chain[1].v == -4.);

    ParticleState p3{1., 6., 0.};
    chain.push_back(p3);

    chain.evolve(1.0);

    CHECK(chain[0].v == -8.);
    CHECK(chain[0].x == 0.);

    CHECK(chain[1].v == 0.);
    CHECK(chain[1].x == 6.);

    CHECK(chain[2].v == 8.);
    CHECK(chain[2].x == 12.);
  }
}