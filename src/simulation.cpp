#include "simulation.hpp"
#include <algorithm>
#include <cassert>
#include <memory>
#include <vector>
#include "infection.hpp"
#include "motion.hpp"
#include "population.hpp"

bool Simulation::check_everyone_position() const
{
  auto const check_position = [=](Person const& person) {
    return (person.position.x >= 0 && person.position.x <= state_.size &&
            person.position.y >= 0 && person.position.y <= state_.size);
  };

  auto const check_people_position = [&](People const& people) {
    auto it = std::find_if_not(people.begin(), people.end(), check_position);
    return (it == people.end());
  };

  return check_people_position(state_.population.S) &&
         check_people_position(state_.population.I) &&
         check_people_position(state_.population.R);
}

Simulation::Simulation(Simulation_State& state,
                       G_Motion& motion,
                       G_Infection& infection)
    : state_{state}, motion_{motion}, infection_{infection}
{
  assert(state_.size > 0);
  assert(check_everyone_position());
}

void Simulation::evolve()
{
  motion_.update(state_.population, state_.size);
  assert(check_everyone_position());
  infection_.update(state_.population, state_.ticks);
  ++state_.ticks;
}