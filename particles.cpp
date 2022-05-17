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
  ImGui::SFML::Init(*window);

  x = static_cast<float>(window->getSize().x) / 2;
  y = static_cast<float>(window->getSize().y) / 2;
  
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


  vertices[4 * index + 0].position = sf::Vector2f(x,y);
  vertices[4 * index + 1].position = sf::Vector2f(x + size,y);
  vertices[4 * index + 2].position = sf::Vector2f(x + size, y + size);
  vertices[4 * index + 3].position = sf::Vector2f(x,y + size);

  //color = sf::Color(0,255,0,255);
  //color = sf::Color(rand() % 255, rand() % 255, rand() % 255, rand() % 255);
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
  sf::Clock clock;
  float imcolor[4] = { (float)0 / 255, (float)255 / 255, (float)64 / 255, (float)64 / 255 };
  int imsize = size;
  int imx = x, imy = y;
  while(window->isOpen()){
    sf::Event e;
    while(window->pollEvent(e)){
      ImGui::SFML::ProcessEvent(*window, e);
      if(e.type == sf::Event::Closed){
        window->close();
      }
    }

    ImGui::SFML::Update(*window, clock.restart());

    ImGui::Begin("Terminal Root");
    ImGui::Button("Particle System");
    ImGui::ColorEdit4("Particle Color", imcolor);
    ImGui::SliderInt("Size", &imsize, 2, 40);
    ImGui::SliderInt("Position x", &imx, 0, 1360);
    ImGui::SliderInt("Position y", &imy, 0, 768);
    ImGui::End();

    x = imx;
    y = imy;
    size = imsize;

    color = sf::Color(
      (int)(imcolor[0] * 255),
      (int)(imcolor[1] * 255),
      (int)(imcolor[2] * 255),
      (int)(imcolor[3] * 255)
    );

    update();

    window->clear(sf::Color::Black);
    window->draw(vertices);
    ImGui::SFML::Render(*window);
    window->display();
  }
  ImGui::SFML::Shutdown();
}
