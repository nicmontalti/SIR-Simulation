#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <algorithm>
#include <cassert>
#include <random>
#include <typeinfo>
#include <vector>
#include "evolution.hpp"

template <class Motion = Random_Motion, class Infection = Simple_Infection>
class Simulation
{
  int size_;
  SIR_population population_;
  Motion motion_;
  Infection infection_;

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

    return check_people_position(population_.S) &&
           check_people_position(population_.I) &&
           check_people_position(population_.R);
  };

 public:
  Simulation(int size, SIR_population const& population = SIR_population{})
      : size_{size}
      , population_{population}
      , motion_{size_, population_}
      , infection_{population_}
  {
    assert(size_ > 0);
    assert((std::is_base_of<G_Motion, Motion>()));
    assert((std::is_base_of<G_Infection, Infection>()));
    assert(check_everyone_position());
  }

  Simulation(int size, int S, int I, int R)
      : size_{size}
      , population_{People(S), People(I), People(R)}
      , motion_{size_, population_}
      , infection_{population_}
  {
    assert(size_ > 0);
    assert((std::is_base_of<G_Motion, Motion>()));
    assert((std::is_base_of<G_Infection, Infection>()));

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> position_distribution{
        0., static_cast<double>(size_)};

    auto new_starting_state = [&]() {
      double const x = position_distribution(gen);
      double const y = position_distribution(gen);
      return Person{Position{x, y}, Velocity{0., 0.}};
    };

    std::generate(
        population_.S.begin(), population_.S.end(), new_starting_state);
    std::generate(
        population_.I.begin(), population_.I.end(), new_starting_state);
    std::generate(
        population_.R.begin(), population_.R.end(), new_starting_state);

    assert(check_everyone_position());
  }

  Simulation(int size, int N) : Simulation(size, N - 1, 1, 0)
  {
  }

  auto& get_population() const
  {
    return population_;
  }
  int size() const
  {
    return size_;
  };
};

#endif
