#ifndef CHAIN_HPP
#define CHAIN_HPP
#include <vector>

#include "hooke.hpp"

class Chain {
  Hooke m_inter;
  std::vector<ParticleState> m_particle_states;

 public:
  Chain(Hooke const& inter);
  void push_back(ParticleState const& ps);
  int size() const;

  void evolve(double delta_t);
  std::vector<ParticleState> const& state() const;

  ParticleState& operator[](int);
};

#endif