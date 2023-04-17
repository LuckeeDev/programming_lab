#include <iostream>
#include <random>

#include "statistics.hpp"

int main() {
  pf::Sample data{};

  std::random_device r;
  std::default_random_engine eng(r());
  std::normal_distribution<double> dist;

  for (int i = 0; i < 1000000; i++) {
    data.add(dist(eng));
  }

  const auto stat{data.statistics()};
  std::cout << "- mean: " << stat.mean << '\n'
            << "- sigma: " << stat.sigma << '\n';
}