#include "particles.hpp"

Particles::Particles(){
  count = 1024;
  size = 8;

  window = std::make_shared<sf::RenderWindow>(
    sf::VideoMode(1360,768),
    "Particles System",
    sf::Style::Titlebar | sf::Style::Close
  );
  window->setFramerateLimit(60);
  window->setPosition(sf::Vector2i(0,0));
  reset_particles();
}

void Particles::reset_particles(){
  m_particles = std::vector<Particle>(count);
  vertices = sf::VertexArray(sf::Quads, count * 4);

  for (std::size_t i{}; i < m_particles.size(); ++i){
   reset_particle(i, true); 
  }
}

void Particles::reset_particle(std::size_t index, bool start = false){
  float x = static_cast<float>(window->getSize().x) / 2;
  float y = static_cast<float>(window->getSize().y) / 2;

  vertices[4 * index + 0].position = sf::Vector2f(x,y);
  vertices[4 * index + 1].position = sf::Vector2f(x + size,y);
  vertices[4 * index + 2].position = sf::Vector2f(x + size, y + size);
  vertices[4 * index + 3].position = sf::Vector2f(x,y + size);

  sf::Color color;
  //color = sf::Color(0,255,0,255);
  //color = sf::Color(rand() % 255, rand() % 255, rand() % 255, rand() % 255);
  color = sf::Color(0, rand() % 255, 0, rand() % 255);
  if(start){
    color.a = 0;
  }

  for (std::size_t i{}; i < 4; ++i){
    vertices[4 * index + i].color = color;
  }

  sf::Vector2f pos = {
    static_cast<float>(rand()) / (float)RAND_MAX * 8 - 4,
    static_cast<float>(rand()) / (float)RAND_MAX * 8 - 4
  };

  m_particles[index].velocity = pos;
  m_particles[index].lifetime = 30 + rand() % 60;
  
}

void Particles::update(){
  for (std::size_t i{}; i < m_particles.size(); ++i){
    if( m_particles[i].lifetime == 0 ){
      reset_particle(i);
    }
    vertices[4 * i + 0].position += m_particles[i].velocity;
    vertices[4 * i + 1].position += m_particles[i].velocity;
    vertices[4 * i + 2].position += m_particles[i].velocity;
    vertices[4 * i + 3].position += m_particles[i].velocity;   
    --m_particles[i].lifetime;
  }
}

void Particles::run(){
  while(window->isOpen()){
    sf::Event e;
    while(window->pollEvent(e)){
      if(e.type == sf::Event::Closed){
        window->close();
      }
    }

    update();

    window->clear(sf::Color::Black);
    window->draw(vertices);
    window->display();
  }
}
