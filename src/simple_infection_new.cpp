#include <algorithm>
#include <cassert>
#include <cmath>
#include "infection.hpp"

Simple_Infection::Simple_Infection(double limiting_distance,
                                   float infection_probability,
                                   float recovery_probability)
    : limiting_distance_{limiting_distance}
    , infection_probability_{infection_probability}
    , recovery_probability_{recovery_probability}
    , random_seed_{std::random_device{}()}
    , probability_distribution_{0.F, 1.F}
{
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

void Simple_Infection::sane_to_infected(SIR_Population& population, int ticks)
{
  auto it_sane = population.S.begin();
  auto last_sane = population.S.end();

  auto first_to_check = population.I.begin();
  auto check_end = population.I.end();

  auto check_infection = [&](Person infected) {
    if (distance(*it_sane, infected) < limiting_distance_) {
      return probability_distribution_(random_seed_) < infection_probability_;
    }
    return false;
  };

  while (it_sane != last_sane) {
    auto infecting_person =
        std::find_if(first_to_check, check_end, check_infection);

    if (infecting_person != check_end) {
      // Updating person status
      it_sane->sub_status = Sub_Status::Infective;
      it_sane->time_of_infection = ticks;

      // Push_back person to Infective vector
      population.I.push_back(*it_sane);

      // Fast erase swapping with back and popping
      std::iter_swap(it_sane, population.S.rbegin());
      population.S.pop_back();

      // Updating last_sane, it_sane is already at next person
      last_sane = population.S.end();
    } else {
      // Updating it_sane to next person
      ++it_sane;
    }
  }
}

void Simple_Infection::infected_to_recovered(SIR_Population& population,
                                             int ticks)
{
  auto it_infected = population.I.begin();
  auto last_infected = population.I.end();
  while (it_infected != last_infected) {
    if (probability_distribution_(random_seed_) < recovery_probability_) {
      // Updating person status
      it_infected->sub_status = Sub_Status::Recovered;
      it_infected->time_of_recovery = ticks;

      // Push_back person to Recovered vector
      population.R.push_back(*it_infected);

      // Fast erase swapping with back and popping
      std::iter_swap(it_infected, population.I.rbegin());
      population.I.pop_back();

      // Updating last_infected, it_infected is already at next person
      last_infected = population.I.end();
    } else {
      // Updating it_infected to next person to check
      ++it_infected;
    }
  }
}