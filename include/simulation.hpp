#ifndef SIR_SIMULATION_HPP
#define SIR_SIMULATION_HPP

#include "infection.hpp"
#include "motion.hpp"
#include "population.hpp"

class Simulation
{
  Simulation_State state_;
  G_Motion& motion_;
  G_Infection& infection_;

  bool check_everyone_position() const;

 public:
  Simulation(Simulation_State& state, G_Motion& motion, G_Infection& infection);

  void evolve();

  Simulation_State const& get_state() const
  {
    return state_;
  }
};

#endif
