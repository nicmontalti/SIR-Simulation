#ifndef SIR_SIMULATION_HPP
#define SIR_SIMULATION_HPP

#include "infection.hpp"
#include "motion.hpp"
#include "population.hpp"

namespace sir {

class Simulation
{
  Simulation_State state_;
  G_Motion& motion_;
  G_Infection& infection_;

 public:
  Simulation(Simulation_State& state, G_Motion& motion, G_Infection& infection);

  void update();
  bool is_over()
  {
    return state_.population.I.size() == 0;
  }

  Simulation_State const& get_state() const
  {
    return state_;
  }
};

}  // namespace sir

#endif
