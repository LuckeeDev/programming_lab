#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <cmath>
#include <numeric>
#include <vector>

#include "doctest.h"

struct Statistics {
  double mean{};
  double sigma{};
  double mean_err{};
};

class Sample {
  std::vector<double> entries_{};

 public:
  void add(double x) { entries_.push_back(x); }

  void clear() { entries_.clear(); }

  Statistics statistics() const {
    int N_ = entries_.size();

    if (N_ == 0) {
      throw std::runtime_error("No data was added.");
    }

    double sum_x_ = std::accumulate(entries_.begin(), entries_.end(), 0.);

    double mean = sum_x_ / N_;

    if (N_ == 1) {
      return Statistics{mean, -1, -1};
    }

    double sum_x2_ = std::inner_product(entries_.begin(), entries_.end(),
                                        entries_.begin(), 0);

    double sigma =
        std::sqrt(sum_x2_ / (N_ - 1) - std::pow(sum_x_, 2) / (N_ * (N_ - 1)));

    double mean_err = sigma / std::sqrt(N_);

    if (sigma == 0) {
      return Statistics{mean, -1, -1};
    }

    return Statistics{mean, sigma, mean_err};
  }
};

TEST_CASE("Testing the class handling a floating point data sample") {
  Sample sample;

  SUBCASE("Calling with no data throws an exception") {
    CHECK_THROWS(sample.statistics());
  }

  SUBCASE("Calling with just one point returns undefined sigma") {
    sample.add(1.0);

    auto result = sample.statistics();

    CHECK(result.mean == doctest::Approx(1.0));
    CHECK(result.sigma == doctest::Approx(-1.0));
    CHECK(result.mean_err == doctest::Approx(-1.0));
  }

  SUBCASE("Calling with two equal points returns undefined sigma") {
    sample.add(2.0);
    sample.add(2.0);

    auto result = sample.statistics();

    CHECK(result.mean == doctest::Approx(2.0));
    CHECK(result.sigma == doctest::Approx(-1.0));
    CHECK(result.mean_err == doctest::Approx(-1.0));
  }

  SUBCASE("Calling with some data should return the predicted output") {
    sample.add(1.0);
    sample.add(1.0);
    sample.add(2.0);
    sample.add(4.0);

    auto result = sample.statistics();

    CHECK(result.mean == doctest::Approx(2.0));
    CHECK(result.sigma == doctest::Approx(1.414214));
    CHECK(result.mean_err == doctest::Approx(0.707107));
  }
};