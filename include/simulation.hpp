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
  Simulation(int size,
             Population const& population,
             G_Motion& motion,
             G_Infection& infection);

  Simulation_State const& evolve();

  Simulation_State const& get_state() const
  {
    return state_;
  }

  int size() const
  {
    return state_.size;
  };
};

#endif
