#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include "SIR_population.hpp"
#include "infection.hpp"
#include "motion.hpp"

#include <cassert>

struct Simulation_State {
  SIR_Population population;
  unsigned int ticks;

  Simulation_State(SIR_Population i_population)
      : ticks{0}, population{i_population} {}
};

template <class Motion = Random_Motion, class Infection = Simple_Infection>
class Simulation {
  const int size_;
  Simulation_State state;

  Motion motion_;
  Infection infection_;

  bool check_everyone_position() { return true; };

public:
  Simulation(int size, SIR_Population population = {})
      : size_{size}, state{population}, motion_{size_, state.population,
                                                state.ticks},
        infection_{size_, state.population, state.ticks} {}

  Simulation_State const &evolve() {
    motion_.move();
    assert(check_everyone_position());
    infection_.update();
    return getState();
  }

  Simulation_State const &getState() const { return state; }
};

#endif