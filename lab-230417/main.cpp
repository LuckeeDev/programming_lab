#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <random>

#include "statistics.hpp"

class custom_generator {
  std::random_device r_;
  std::default_random_engine eng{r_()};
  std::normal_distribution<double> dist;

 public:
  double operator()() { return dist(eng); }
};

int main() {
  pf::Sample data{};
  auto inserter = std::back_inserter(data);

  std::ifstream input("./data.txt");
  std::ofstream output("./result.txt");

  if (!output) {
    std::cout << "The output file could not be open." << '\n';
  }

  std::generate_n(inserter, 100000, custom_generator{});

  const auto stat{data.statistics()};

  output << "- mean: " << stat.mean << '\n'
         << "- sigma: " << stat.sigma << '\n'
         << "- median: " << stat.median << '\n'
         << "- mean err: " << stat.mean_err << '\n';
}