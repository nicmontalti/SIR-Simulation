#include "simulation.hpp"

#include <cassert>

template<>
void Simulation<>::evolve(int ticks) {
  assert(ticks > 0);
  for (int i = 0; i != ticks; i++) {
    motion.move();
    assert(check_everyone_position());

    infection.update();
  }
}