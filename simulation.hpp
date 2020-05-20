#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <memory>
#include "SIR_population.hpp"
#include "infection.hpp"
#include "motion.hpp"

using std::make_unique;
using std::unique_ptr;

struct Simulation_State
{
  SIR_Population population;
  unsigned int ticks;

  Simulation_State(SIR_Population i_population)
      : ticks{0}, population{i_population}
  {
  }
};

class Simulation
{
  int size_;
  Simulation_State state_;
  unique_ptr<G_Motion> motion_;
  unique_ptr<G_Infection> infection_;

  bool check_everyone_position();

 public:
  Simulation(
      int size,
      SIR_Population const& population = SIR_Population{},
      unique_ptr<G_Motion> motion = make_unique<Random_Motion>(),
      unique_ptr<G_Infection> infection = make_unique<Simple_Infection>());

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
