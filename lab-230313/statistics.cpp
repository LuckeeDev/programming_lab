#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <cmath>
#include <numeric>
#include <vector>

#include "doctest.h"

struct Statistics {
  double mean{};
  double sigma{};
  double mean_err{};
  double median{};
};

class Sample {
  std::vector<double> entries_{};

 public:
  const auto& entries() const { return entries_; }
  auto& entries() { return entries_; }

  void add(double x) { entries_.push_back(x); }

  void clear() { entries_.clear(); }

  int size() { return entries_.size(); }

  bool remove(double point) {
    auto position = std::find(entries_.begin(), entries_.end(), point);

    if (position == entries_.end()) {
      return false;
    }

    entries_.erase(position);

    return true;
  }

  Statistics statistics() const {
    auto entries{entries_};
    auto e_begin{entries.begin()};
    auto e_end{entries.end()};

    std::sort(e_begin, e_end);

    int N = entries.size();

    if (N == 0) {
      throw std::runtime_error("No data was added.");
    }

    double sum_x = std::accumulate(e_begin, e_end, 0.);

    double mean = sum_x / N;

    if (N == 1) {
      return Statistics{mean, -1, -1, mean};
    }

    double sum_x2 = std::inner_product(e_begin, e_end, e_begin, 0);

    double sigma =
        std::sqrt(sum_x2 / (N - 1) - std::pow(sum_x, 2) / (N * (N - 1)));

    double mean_err = sigma / std::sqrt(N);

    double median{};

    if (N % 2 == 0) {
      median = (entries[N / 2 - 1] + entries[N / 2]) / 2;
    } else {
      median = entries[(N - 1) / 2];
    }

    if (sigma == 0) {
      return Statistics{mean, -1, -1, median};
    }

    return Statistics{mean, sigma, mean_err, median};
  }
};

Sample operator+(const Sample& l, const Sample& r) {
  Sample sum{l};

  std::vector<double>& sum_vector{sum.entries()};

  sum_vector.insert(sum_vector.end(), r.entries().begin(), r.entries().end());

  return sum;
}

TEST_CASE("Testing the class handling a floating point data sample") {
  Sample sample;

  REQUIRE(sample.size() == 0);

  SUBCASE("Calling with no data throws an exception") {
    CHECK_THROWS(sample.statistics());
  }

  SUBCASE("Calling with just one point returns undefined sigma") {
    sample.add(1.0);

    auto result = sample.statistics();

    CHECK(result.mean == doctest::Approx(1.0));
    CHECK(result.sigma == doctest::Approx(-1.0));
    CHECK(result.mean_err == doctest::Approx(-1.0));
    CHECK(result.median == doctest::Approx(1.0));
  }

  SUBCASE("Calling with two equal points returns undefined sigma") {
    sample.add(2.0);
    sample.add(2.0);

    auto result = sample.statistics();

    CHECK(result.mean == doctest::Approx(2.0));
    CHECK(result.sigma == doctest::Approx(-1.0));
    CHECK(result.mean_err == doctest::Approx(-1.0));
    CHECK(result.median == doctest::Approx(2.0));
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
    CHECK(result.median == doctest::Approx(1.5));
  }

  SUBCASE("Removing an existing point should return true") {
    sample.add(1.5);
    sample.add(2.0);

    CHECK(sample.remove(2.0) == true);
    CHECK(sample.size() == 1);
  }

  SUBCASE("Removing a non existing point should return false") {
    sample.add(1.5);
    sample.add(2.0);

    CHECK(sample.remove(1.9) == false);
    CHECK(sample.size() == 2);
  }

  SUBCASE("Adding two sample instances") {
    sample.add(1);

    Sample sample_two;
    sample_two.add(2);

    auto sum = sample + sample_two;

    CHECK(sum.size() == 2);

    if (sum.size() == 2) {
      CHECK(sum.entries()[0] == doctest::Approx(1.0));
      CHECK(sum.entries()[1] == doctest::Approx(2.0));
    }
  }
};