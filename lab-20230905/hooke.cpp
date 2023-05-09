#include "hooke.hpp"

#include <cassert>
#include <cmath>

Hooke::Hooke(double k, double l) : m_k{k}, m_l{l} { assert(k > 0. || l > 0.); };

double Hooke::operator()(const ParticleState& a, const ParticleState& b) const {
  auto dx = std::abs(a.x - b.x);
  return -m_k * (m_l - dx);
}