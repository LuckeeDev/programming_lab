#include <SFML/Graphics.hpp>
#include <cmath>
#include <iomanip>
#include <iostream>

#include "chain.hpp"

int main() {
  double k;
  double l;
  double p_m;
  double delta_x;

  std::cout << "Input k (N): ";
  std::cin >> k;

  std::cout << "Input l (m): ";
  std::cin >> l;

  std::cout << "Input particle mass (kg): ";
  std::cin >> p_m;

  std::cout << "Input delta x (m): ";
  std::cin >> delta_x;

  Hooke const hooke{k, l};

  Chain chain(hooke);

  double p_x{0.0};
  double const p_v{0.0};

  std::generate_n(std::back_inserter(chain), 10, [&]() mutable {
    ParticleState ps{p_m, p_x, p_v};
    p_x = p_x + delta_x;
    return ps;
  });

  sf::RenderWindow window(sf::VideoMode(1100, 600), "Chain of springs");

  sf::Clock clock;

  window.setFramerateLimit(60);

  // run the program as long as the window is open
  while (window.isOpen()) {
    // check all the window's events that were triggered since the last
    // iteration of the loop
    sf::Event event;
    while (window.pollEvent(event)) {
      // "close requested" event: we close the window
      if (event.type == sf::Event::Closed) window.close();
    }

    auto delta_t = clock.restart().asSeconds();
    float const evolve_t = 0.001;

    int iterations = std::ceil(delta_t / evolve_t);

    for (int i{}; i < iterations; i++) {
      chain.evolve(evolve_t);
    }

    window.draw(chain);

    // end the current frame
    window.display();
  }
}
