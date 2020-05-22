#include "infection.hpp"
#include <cassert>
#include <cmath>

Simple_Infection::Simple_Infection(int const ticks_frequency,
                                   double limiting_distance,
                                   float infection_probability,
                                   float recovery_probability)
    : ticks_frequency_{ticks_frequency}
    , limiting_distance_{limiting_distance}
    , infection_probability_{infection_probability}
    , recovery_probability_{recovery_probability}
    , random_seed_{std::random_device{}()}
    , probability_distribution_{0.F, 1.F}
{
  assert(ticks_frequency_ > 0);
  assert(limiting_distance_ > 0);
  assert(infection_probability_ >= 0 && infection_probability_ <= 1);
  assert(recovery_probability_ >= 0 && recovery_probability_ <= 1);
}

double Simple_Infection::distance(Person const& left, Person const& right)
{
  double const x_distance = left.position.x - right.position.x;
  double const y_distance = left.position.y - right.position.y;
  return std::sqrt(x_distance * x_distance + y_distance * y_distance);
}

void Simple_Infection::sane_to_infected(SIR_Population& population)
{
  // using auto& it_sane
  // error: cannot bind non-const lvalue reference of type
  // ‘__gnu_cxx::__normal_iterator<Person*, std::vector<Person> >&’ to an
  // rvalue of type ‘std::vector<Person>::iterator {aka
  // __gnu_cxx::__normal_iterator<Person*, std::vector<Person> >}’
  auto last_sane = population.S.end();
  auto last_infected = population.I.end();
  for (auto it_sane = population.S.begin(); it_sane != last_sane; ++it_sane) {
    for (auto it_infected = population.I.begin(); it_infected != last_infected;
         ++it_infected) {
      if (distance(*it_sane, *it_infected) < limiting_distance_) {
        if (probability_distribution_(random_seed_) < infection_probability_) {
          population.I.push_back(*it_sane);
          last_infected = population.I.end();
          std::iter_swap(it_sane, std::prev(last_sane));
          it_sane = std::prev(it_sane);
          population.S.pop_back();
          last_sane = population.S.end();
          break;
        }
      }
    }
  }
}

void Simple_Infection::infected_to_recovered(SIR_Population& population)
{
  auto last_infected = population.I.end();
  for (auto it_infected = population.I.begin(); it_infected != last_infected;
       ++it_infected) {
    if (probability_distribution_(random_seed_) < recovery_probability_) {
      population.R.push_back(*it_infected);
      std::iter_swap(it_infected, std::prev(last_infected));
      it_infected = std::prev(it_infected);
      population.I.pop_back();
      last_infected = population.I.end();
    }
  }
}