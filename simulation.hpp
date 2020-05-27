#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <memory>
#include "SIR_population.hpp"
#include "infection.hpp"
#include "motion.hpp"

struct Simulation_State
{
  SIR_Population population;
  unsigned int ticks;

  Simulation_State(SIR_Population i_population)
      : population{i_population}, ticks{0}
  {
  }
};

class Simulation
{
  int size_;
  Simulation_State state_;
  G_Motion& motion_;
  G_Infection& infection_;

  bool check_everyone_position();

 public:
  Simulation(int size,
             SIR_Population const& population,
             G_Motion& motion,
             G_Infection& infection);

  Simulation_State const& evolve();

  Simulation_State const& get_state() const
  {
    return state_;
  }

  int size() const
  {
    return size_;
  };
};

#endif
