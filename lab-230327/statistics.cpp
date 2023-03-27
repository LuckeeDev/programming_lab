#include "statistics.h"

#include <algorithm>
#include <cmath>
#include <numeric>
#include <stdexcept>
#include <vector>

int pf::Sample::size() const { return entries_.size(); }
void pf::Sample::add(double x) { entries_.push_back(x); }

std::vector<double>& pf::Sample::entries() { return entries_; }
const std::vector<double>& pf::Sample::entries() const { return entries_; }

bool pf::Sample::remove(double x) {
  auto const it = std::find(entries_.begin(), entries_.end(), x);

  if (it != entries_.end()) {
    entries_.erase(it);
    return true;
  }

  return false;
}

pf::Statistics pf::Sample::statistics() const {
  const int N{size()};

  if (N < 2) {
    throw std::runtime_error{"Not enough entries to run a statistics"};
  }

  struct Sums {
    double x;
    double x2;
  };

  const auto sums = std::accumulate(entries_.begin(), entries_.end(), Sums{},
                                    [](Sums s, double x) {
                                      s.x += x;
                                      s.x2 += x * x;
                                      return s;
                                    });

  const double mean = sums.x / N;
  const double sigma = std::sqrt((sums.x2 - N * mean * mean) / (N - 1));
  const double mean_err = sigma / std::sqrt(N);

  auto entries{entries_};
  std::sort(entries.begin(), entries.end());

  const double median =
      N % 2 == 0 ? (entries[N / 2 - 1] + entries[N / 2]) * 0.5 : entries[N / 2];

  return {mean, sigma, mean_err, median};
}

pf::Sample& pf::Sample::operator+=(const pf::Sample& r) {
  entries_.reserve(size() + r.size());
  entries_.insert(entries_.end(), r.entries().begin(), r.entries().end());
  return *this;
}

pf::Sample pf::operator+(const pf::Sample& l, const pf::Sample& r) {
  pf::Sample sum{l};
  return sum += r;
}