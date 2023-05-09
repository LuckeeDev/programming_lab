#include "chain.hpp"

#include <algorithm>
#include <vector>

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
