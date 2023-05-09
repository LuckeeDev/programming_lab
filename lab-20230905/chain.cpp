#include "chain.hpp"

#include <algorithm>
#include <cmath>
#include <vector>

ParticleState Chain::solve(ParticleState const& ps, double f,
                           double delta_t) const {
  auto a = f / ps.m;
  auto v = ps.v + a * delta_t;
  auto x = ps.x + ps.v * delta_t + 0.5 * a * std::pow(delta_t, 2);

  return ParticleState{ps.m, x, v};
};

Chain::Chain(const Hooke& inter) : m_inter{inter} {};

void Chain::push_back(const ParticleState& ps) {
  auto where = std::find_if(m_particle_states.begin(), m_particle_states.end(),
                            [&](ParticleState current) {
                              if (current.x > ps.x) {
                                return true;
                              }

                              return false;
                            });

  m_particle_states.insert(where, ps);
}

int Chain::size() const { return static_cast<int>(m_particle_states.size()); }

std::vector<ParticleState> const& Chain::state() const {
  return m_particle_states;
}

ParticleState& Chain::operator[](int n) { return m_particle_states[n]; };

void Chain::evolve(double delta_t) {
  auto begin = m_particle_states.begin();
  auto end = m_particle_states.end();

  std::vector<ParticleState> new_states;

  for (auto it = begin; it < end; it++) {
    ParticleState new_state;

    if (it == begin) {
      auto f = m_inter(*it, *(it + 1));
      new_state = solve(*it, f, delta_t);
    } else if (it == begin - 1) {
      auto f = m_inter(*it, *(it - 1));
      new_state = solve(*it, f, delta_t);
    } else {
      auto f1 = m_inter(*it, *(it - 1));
      auto f2 = m_inter(*it, *(it + 1));
      new_state = solve(*it, f1 + f2, delta_t);
    }

    new_states.push_back(new_state);
  }
};
