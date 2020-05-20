#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <algorithm>
#include <cassert>
#include <memory>
#include <random>
#include <typeinfo>
#include <vector>
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

  bool check_everyone_position()
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
  };

 public:
  Simulation(
      int size,
      SIR_Population const& population = SIR_Population{},
      unique_ptr<G_Motion> motion = make_unique<Random_Motion>(),
      unique_ptr<G_Infection> infection = make_unique<Simple_Infection>())
      : size_{size}
      , state_{population}
      , motion_{std::move(motion)}
      , infection_{std::move(infection)}
  {
    assert(size_ > 0);
    assert(check_everyone_position());
  }

  // Simulation(int size, int S, int I, int R)
  //     : size_{size}
  //     , state_{SIR_Population{People(S), People(I), People(R)}}
  //     , motion_{size_, state_.population, state_.ticks}
  //     , infection_{size_, state_.population, state_.ticks}
  // {
  //   assert(size_ > 0);
  //   assert((std::is_base_of<G_Motion, Motion>()));
  //   assert((std::is_base_of<G_Infection, Infection>()));

  //   std::random_device rd;
  //   std::mt19937 gen(rd());
  //   std::uniform_real_distribution<double> position_distribution{
  //       0., static_cast<double>(size_)};

  //   auto new_starting_state = [&]() {
  //     double const x = position_distribution(gen);
  //     double const y = position_distribution(gen);
  //     return Person{Position{x, y}, Velocity{0., 0.}};
  //   };

  //   std::generate(state_.population.S.begin(),
  //                 state_.population.S.end(),
  //                 new_starting_state);
  //   std::generate(state_.population.I.begin(),
  //                 state_.population.I.end(),
  //                 new_starting_state);
  //   std::generate(state_.population.R.begin(),
  //                 state_.population.R.end(),
  //                 new_starting_state);

  //   assert(check_everyone_position());
  // }

  // Simulation(int size, int N) : Simulation(size, N - 1, 1, 0)
  // {
  // }
  Simulation_State const& evolve()
  {
    motion_->move();
    assert(check_everyone_position());
    infection_->update();
    return get_state();
  }
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
