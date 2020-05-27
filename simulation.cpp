#include "simulation.hpp"
#include <algorithm>
#include <cassert>
#include <memory>
#include <vector>
#include "SIR_population.hpp"
#include "infection.hpp"
#include "motion.hpp"

bool Simulation::check_everyone_position()
{
  auto const check_position = [=](Person const& person) {
    return (person.position.x >= 0 && person.position.x <= size_ &&
            person.position.y >= 0 && person.position.y <= size_);
  };

  auto const check_people_position = [&](People const& people) {
    auto it = std::find_if_not(people.begin(), people.end(), check_position);
    return (it == people.end());
  };

  return check_people_position(state_.population.S) &&
         check_people_position(state_.population.I) &&
         check_people_position(state_.population.R);
}

Simulation::Simulation(int size,
                       SIR_Population const& population,
                       G_Motion& motion,
                       G_Infection& infection)
    : size_{size}, state_{population}, motion_{motion}, infection_{infection}
{
  assert(size_ > 0);
  assert(check_everyone_position());
}

Simulation_State const& Simulation::evolve()
{
  motion_.update(state_.population, state_.ticks, size_);
  assert(check_everyone_position());
  infection_.update(state_.population, state_.ticks);
  return get_state();
}