#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <random>

#include "statistics.hpp"

namespace pf {
class custom_generator {
  std::default_random_engine eng_;
  std::normal_distribution<double> dist_;

 public:
  custom_generator() {
    std::random_device r;
    eng_ = std::default_random_engine(r());
  };

  double operator()() { return dist_(eng_); }
};
}  // namespace pf

int main() {
  pf::Sample data{};

  std::ifstream input("./data.txt");
  std::ofstream output("./result.txt");

  if (!output) {
    std::cout << "The output file could not be open." << '\n';
  }

  auto inserter = std::back_inserter(data);
  pf::custom_generator gen;

  std::generate_n(inserter, 100000, gen);

  const auto stat{data.statistics()};

  output << "- mean: " << stat.mean << '\n'
         << "- sigma: " << stat.sigma << '\n'
         << "- median: " << stat.median << '\n'
         << "- mean err: " << stat.mean_err << '\n';
}