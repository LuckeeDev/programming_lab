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

  void clear() {
    N_ = 0;
    sum_x_ = 0;
    sum_x2_ = 0;
  }

  Statistics statistics() const {
    if (N_ == 0) {
      throw std::runtime_error("No data was added.");
    }

    double mean = sum_x_ / N_;
    double sigma = std::sqrt(sum_x2_ / N_ - std::pow(mean, 2));
    double mean_err = sigma / std::sqrt(N_);

    return Statistics{mean, sigma, mean_err};
  }
};

TEST_CASE("Testing the class handling a floating point data sample") {
  Sample sample;

  CHECK_THROWS(sample.statistics());

  sample.add(1.0);

  auto result = sample.statistics();

  CHECK(result.mean == doctest::Approx(1.0));
  CHECK(result.sigma == doctest::Approx(0.0));
  CHECK(result.mean_err == doctest::Approx(0.0));

  sample.add(1.0);

  result = sample.statistics();

  CHECK(result.mean == doctest::Approx(1.0));
  CHECK(result.sigma == doctest::Approx(0.0));
  CHECK(result.mean_err == doctest::Approx(0.0));

  sample.add(2.0);
  sample.add(4.0);

  result = sample.statistics();

  CHECK(result.mean == doctest::Approx(2.0));
  CHECK(result.sigma == doctest::Approx(1.224745));
  CHECK(result.mean_err == doctest::Approx(0.612372));
};