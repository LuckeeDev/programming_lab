#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "statistics.hpp"

#include "doctest.h"

TEST_CASE("Testing the class handling a floating point data sample") {
  pf::Sample sample;

  REQUIRE(sample.size() == 0);

  SUBCASE("Calling statistics() with no points throws") {
    CHECK_THROWS(sample.statistics());
  }

  SUBCASE("Calling statistics() with one point throws") {
    sample.push_back(4.0);
    CHECK_THROWS(sample.statistics());
  }

  SUBCASE("Calling statistics() with two points") {
    sample.push_back(1.0);
    sample.push_back(2.0);
    const auto result = sample.statistics();
    CHECK(result.mean == doctest::Approx(1.5));
    CHECK(result.sigma == doctest::Approx(0.70710678));
    CHECK(result.mean_err == doctest::Approx(0.5));
    CHECK(result.median == doctest::Approx(1.5));
  }

  SUBCASE("Calling statistics() with two identical points") {
    sample.push_back(10.0);
    sample.push_back(10.0);
    const auto result = sample.statistics();
    CHECK(result.mean == doctest::Approx(10.0));
    CHECK(result.sigma == doctest::Approx(0.0));
    CHECK(result.mean_err == doctest::Approx(0.0));
    CHECK(result.median == doctest::Approx(10.0));
  }

  SUBCASE("Calling statistics() with five points") {
    sample.push_back(1.5);
    sample.push_back(2.0);
    sample.push_back(2.5);
    sample.push_back(3.0);
    sample.push_back(3.5);
    const auto result = sample.statistics();
    CHECK(result.mean == doctest::Approx(2.5));
    CHECK(result.sigma == doctest::Approx(0.79056942));
    CHECK(result.mean_err == doctest::Approx(0.35355339));
    CHECK(result.median == doctest::Approx(2.5));
  }

  SUBCASE("Removing an existing point") {
    sample.push_back(1.5);
    sample.push_back(2.0);
    CHECK(sample.remove(2.0) == true);
    CHECK(sample.size() == 1);
  }

  SUBCASE("Removing a non existing point") {
    sample.push_back(1.5);
    sample.push_back(2.0);
    CHECK(sample.remove(1.9) == false);
    CHECK(sample.size() == 2);
  }

  SUBCASE("Testing sum operator") {
    sample.push_back(1);
    pf::Sample sample_two;
    sample_two.push_back(2);
    auto sum = sample + sample_two;
    CHECK(sum.size() == 2);
    if (sum.size() == 2) {
      CHECK(sum.entries()[0] == doctest::Approx(1.0));
      CHECK(sum.entries()[1] == doctest::Approx(2.0));
    }
  }
}