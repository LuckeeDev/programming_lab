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

  double mean() { return this->sum_x_ / this->N_; }

  double sigma() {
    return std::sqrt(this->sum_x2_ / this->N_ - std::pow(this->mean(), 2));
  }

  double mean_err() { return this->sigma() / std::sqrt(this->N_); }

 public:
  void add(double x) {
    this->N_ += 1;
    this->sum_x_ += x;
    this->sum_x2_ += std::pow(x, 2);
  }

  Statistics statistics() {
    double mean = this->mean();
    double sigma = this->sigma();
    double mean_err = this->mean_err();

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