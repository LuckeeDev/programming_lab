#ifndef CHAIN_HPP
#define CHAIN_HPP
#include <SFML/Graphics.hpp>
#include <vector>

#include "hooke.hpp"

class Chain : public sf::Drawable {
 private:
  Hooke m_inter;
  std::vector<ParticleState> m_particle_states;

  ParticleState solve(ParticleState const& ps, double f, double delta_t) const;
  void sorted_insert(ParticleState const& ps, std::vector<ParticleState>&);

  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

 public:
  Chain(Hooke const& inter);
  void push_back(ParticleState const& ps);
  int size() const;

  void evolve(double delta_t);
  std::vector<ParticleState> const& state() const;

  ParticleState& operator[](int);

  using value_type = ParticleState;
};

#endif