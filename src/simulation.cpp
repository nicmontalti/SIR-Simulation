#include "simulation.hpp"

using namespace sir;

Simulation::Simulation(Simulation_State& state,
                       G_Motion& motion,
                       G_Infection& infection)
    : state_{state}, motion_{motion}, infection_{infection}
{
  state_.check_everyone_position();
  update();
}

void Simulation::update()
{
  motion_.update(state_.population, state_.size);
  state_.check_everyone_position();
  infection_.update(state_.population, state_.ticks);
  ++state_.ticks;
}