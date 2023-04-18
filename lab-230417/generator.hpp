#ifndef GENERATOR_HPP
#define GENERATOR_HPP

#include <random>

namespace pf {
class generator {
  std::default_random_engine eng_;
  std::uniform_real_distribution<double> dist_;

 public:
  generator(int min, int max);

  double operator()();
};
}  // namespace pf

#endif