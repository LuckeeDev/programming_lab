#include <fstream>
#include <iostream>
#include <random>

#include "statistics.hpp"

int main() {
  pf::Sample data{};

  std::ifstream input("./data.txt");

  std::string s;

  while (std::getline(input, s)) {
    double x = std::stod(s);
    data.add(x);
  }

  const auto stat{data.statistics()};
  std::cout << "- mean: " << stat.mean << '\n'
            << "- sigma: " << stat.sigma << '\n'
            << "- median: " << stat.median << '\n'
            << "- mean err: " << stat.mean_err << '\n';
}