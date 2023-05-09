#ifndef HOOKE_HPP
#define HOOKE_HPP

struct ParticleState {
  double m{};
  double x{};
  double v{};
};

class Hooke {
  double m_k;
  double m_l;

 public:
  Hooke(double, double);
  double operator()(const ParticleState&, const ParticleState&) const;
};

#endif