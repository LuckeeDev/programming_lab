#include "chain.hpp"

#include <cmath>
#include <iostream>
#include <numeric>
#include <vector>

ParticleState Chain::solve(ParticleState const& ps, double f,
                           double delta_t) const {
  auto a = f / ps.m;
  auto v = ps.v + a * delta_t;
  auto x = ps.x + ps.v * delta_t + 0.5 * a * std::pow(delta_t, 2);

  return ParticleState{ps.m, x, v};
};

Chain::Chain(const Hooke& inter) : m_inter{inter} {};

void Chain::sorted_insert(ParticleState const& ps,
                          std::vector<ParticleState>& v) {
  auto where = std::find_if(v.begin(), v.end(), [&](ParticleState current) {
    if (current.x > ps.x) {
      return true;
    }

    return false;
  });

  v.insert(where, ps);
};

void Chain::push_back(const ParticleState& ps) {
  sorted_insert(ps, m_particle_states);
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
    } else if (it == end - 1) {
      auto f = m_inter(*it, *(it - 1));
      new_state = solve(*it, -f, delta_t);
    } else {
      auto f1 = m_inter(*it, *(it - 1));
      auto f2 = m_inter(*it, *(it + 1));
      new_state = solve(*it, -f1 + f2, delta_t);
    }

    new_states.push_back(new_state);
  }

  m_particle_states = new_states;
};

void Chain::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  float const SCALE_FACTOR = 9000.f;

  target.clear(sf::Color::White);

  auto begin = m_particle_states.begin();
  auto end = m_particle_states.end();

  auto c_m =
      std::accumulate(begin, end, 0.f,
                      [](const float& acc, const ParticleState& current) {
                        return acc + current.x * current.m;
                      }) /
      std::accumulate(begin, end, 0.f,
                      [](const float& acc, const ParticleState& current) {
                        return acc + current.m;
                      });

  for (auto it = begin; it < end; it++) {
    sf::CircleShape circle(30.f);
    circle.setPosition(static_cast<float>(it->x) * SCALE_FACTOR, 270.f);
    circle.move(505.f - c_m * SCALE_FACTOR, 0.f);
    circle.setOutlineColor(sf::Color::Black);
    circle.setOutlineThickness(3.f);

    target.draw(circle);
  };
}
