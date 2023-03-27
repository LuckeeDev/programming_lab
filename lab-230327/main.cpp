#include <iostream>
#include <stdexcept>
#include <string>

#include "statistics.h"

enum Command { Add = 'a', Remove = 'r', Calc = 'c', Quit = 'q' };

int main() {
  std::string current;
  pf::Sample sample;

  while (std::getline(std::cin, current)) {
    char command = current[0];
    current.erase(0, 2);

    try {
      if (command == Command::Add) {
        double x = std::stod(current);
        sample.add(x);
      } else if (command == Command::Remove) {
        double x = std::stod(current);
        sample.remove(x);
      } else if (command == Command::Calc) {
        auto statistics = sample.statistics();
        std::cout << "Mean: " << statistics.mean << '\n'
                  << "Mean err: " << statistics.mean_err << '\n'
                  << "Median: " << statistics.median << '\n'
                  << "Sigma: " << statistics.sigma << '\n';
      } else if (command == Command::Quit) {
        break;
      } else {
        std::cout << "Please insert a valid command" << '\n';
      }
    } catch (std::invalid_argument &err) {
      std::cout << "Please insert a valid number after your command" << '\n';
    }
  }
}
