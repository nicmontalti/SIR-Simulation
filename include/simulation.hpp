#ifndef SIR_SIMULATION_HPP
#define SIR_SIMULATION_HPP

#include "infection.hpp"
#include "motion.hpp"
#include "population.hpp"

namespace sir {

struct Simulation_State
{
  int const size;
  Population population;
  int ticks;

  Simulation_State(int i_size, Population i_population = Population{})
      : size{i_size}, population{i_population}, ticks{0}
  {
    assert(size > 0);
    assert(ticks >= 0);
    assert(check_everyone_position());
  }

  Simulation_State(int i_size, int S, int I, int R);

  bool check_everyone_position() const;
};

class Simulation
{
  Simulation_State state_;
  G_Motion& motion_;
  G_Infection& infection_;

 public:
  Simulation(Simulation_State const& state,
             G_Motion& motion,
             G_Infection& infection);

  void update();

  bool is_over() const
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
