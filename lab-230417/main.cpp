#include <fstream>
#include <iostream>
#include <random>

#include "statistics.hpp"

int main() {
  pf::Sample data{};

  std::ifstream input("./data.txt");
  std::ofstream output("./result.txt");

  if (!output) {
    std::cout << "The output file could not be open." << '\n';
  }

  std::string s;

  while (std::getline(input, s)) {
    double x = std::stod(s);
    data.add(x);
  }

  const auto stat{data.statistics()};

  output << "- mean: " << stat.mean << '\n'
         << "- sigma: " << stat.sigma << '\n'
         << "- median: " << stat.median << '\n'
         << "- mean err: " << stat.mean_err << '\n';
}