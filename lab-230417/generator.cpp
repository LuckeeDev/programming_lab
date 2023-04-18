#include "generator.hpp"

#include <iostream>
#include <random>

namespace pf {
generator::generator(int min, int max) {
  if (min != 0 || max != 0) {
    std::uniform_real_distribution<double> dist(min, max);

    dist_ = dist;
  }

  std::random_device r;
  eng_ = std::default_random_engine(r());
}

double generator::operator()() { return dist_(eng_); }
}  // namespace pf