#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <cmath>

#include "doctest.h"

struct Statistics {
  double mean{};
  double sigma{};
  double mean_err{};
};

class Sample {
  int N_{};
  double sum_x_{};
  double sum_x2_{};

 public:
  void add(double x) {
    ++N_;
    sum_x_ += x;
    sum_x2_ += std::pow(x, 2);
  }

  Statistics statistics() const {
    double mean = sum_x_ / N_;
    double sigma = std::sqrt(sum_x2_ / N_ - std::pow(mean, 2));
    double mean_err = sigma / std::sqrt(N_);

    return Statistics{mean, sigma, mean_err};
  }
};

TEST_CASE("Testing the class handling a floating point data sample") {
  Sample sample;

  sample.add(1.0);
  sample.add(2.0);

  auto result = sample.statistics();
  CHECK(result.mean == doctest::Approx(1.5));
  CHECK(result.sigma == doctest::Approx(0.5));
  CHECK(result.mean_err == doctest::Approx(0.35355339));
};