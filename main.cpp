#include "particles.hpp"

int main(){
  auto particles = std::make_shared<Particles>();
  particles->run();
  return 0;
}

