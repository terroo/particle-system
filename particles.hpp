#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

class Particles {
  public:
    struct Particle {
      sf::Vector2f velocity;
      int lifetime;
    };

    std::shared_ptr<sf::RenderWindow> window;
    std::vector<Particle> m_particles;
    sf::VertexArray vertices;
    float size;
    std::size_t count;

    void reset_particles();
    void reset_particle(std::size_t, bool);
    void update();

    Particles();
    void run();
};
