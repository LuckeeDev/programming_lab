#include <SFML/Graphics.hpp>
#include <cmath>
#include <iomanip>
#include <iostream>

#include "chain.hpp"

int main() {
  Hooke const hooke{1.0, 0.01};

  Chain chain(hooke);

  double const p_m{0.05};

  double p_x{0.0};
  double delta_x{0.011};

  for (auto const p_v : {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}) {
    chain.push_back({p_m, p_x, p_v});
    p_x += delta_x;
  }

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
