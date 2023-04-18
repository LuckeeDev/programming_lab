#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

#include "generator.hpp"
#include "statistics.hpp"

enum Commands {
  Clear = 'c',
  Read = 'r',
  Generate = 'g',
  Print = 's',
  Write = 'o',
  Quit = 'q',
  Help = 'h'
};

int main() {
  std::cout << "Type h and hit enter to get help." << '\n';

  std::string s;
  pf::Sample data{};

  while (std::getline(std::cin, s)) {
    auto command = s[0];

    s.erase(0, 2);

    switch (command) {
      case Commands::Clear: {
        data.clear();
        break;
      }

      case Commands::Read: {
        std::string current;

        std::ifstream input(s);

        while (std::getline(input, current)) {
          const auto d = std::stod(current);
          data.push_back(d);
        }

        break;
      }

      case Commands::Generate: {
        const auto first = s.find(' ');
        const auto count = std::stod(s.substr(0, first));
        s.erase(0, first + 1);

        const auto second = s.find(' ');

        double min{}, max{};

        if (second != std::string::npos) {
          min = std::stod(s.substr(0, second));
          s.erase(0, second + 1);
        }

        const auto end = s.find(' ');

        if (end != std::string::npos) {
          std::cout << "Too many arguments!";
          break;
        } else {
          max = std::stod(s.substr(0, end));
        }

        pf::generator generator(min, max);

        std::generate_n(std::back_inserter(data), count, generator);

        break;
      }

      case Commands::Print: {
        const auto stat{data.statistics()};

        std::cout << "- mean: " << stat.mean << '\n'
                  << "- sigma: " << stat.sigma << '\n'
                  << "- median: " << stat.median << '\n'
                  << "- mean err: " << stat.mean_err << '\n';
        break;
      }

      case Commands::Write: {
        std::ofstream output(s);

        if (!output) {
          std::cout << "The file could not be open." << '\n';
          break;
        }

        const auto stat{data.statistics()};

        output << "- mean: " << stat.mean << '\n'
               << "- sigma: " << stat.sigma << '\n'
               << "- median: " << stat.median << '\n'
               << "- mean err: " << stat.mean_err << '\n';

        break;
      }

      case Commands::Quit: {
        return 0;
      }

      case Commands::Help: {
        std::cout
            << "Available commands are:" << '\n'
            << "- c: Clear the data sample" << '\n'
            << "- r FILE_NAME: Read data from a file at path FILE_NAME" << '\n'
            << "- o FILE_NAME: Write statistics to a file at path FILE_NAME"
            << '\n'
            << "- s: Print statistics to terminal" << '\n'
            << "- g COUNT (MIN MAX): Generate COUNT random numbers. "
            << "You can optionally specify the minimum and maximum." << '\n'
            << "- q: Quit" << '\n';

        break;
      }

      default: {
        std::cout
            << "This command does not exist. Type h and hit enter to get help."
            << '\n';
      }
    }
  }
}