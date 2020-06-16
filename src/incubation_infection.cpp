#include "incubation_infection.hpp"
#include <cassert>
#include <cmath>

Incubation_Infection::Incubation_Infection(double limiting_distance,
                                           float infection_probability,
                                           float recovery_probability,
                                           int incubation_time)
    : limiting_distance_{limiting_distance}
    , infection_probability_{infection_probability}
    , recovery_probability_{recovery_probability}
    , incubation_time_{incubation_time}
    , random_seed_{std::random_device{}()}
    , probability_distribution_{0.F, 1.F}
{
  assert(limiting_distance_ > 0);
  assert(infection_probability_ >= 0 && infection_probability_ <= 1);
  assert(recovery_probability_ >= 0 && recovery_probability_ <= 1);
  assert(incubation_time_ >= 0);
}

double Incubation_Infection::distance(Person const& left, Person const& right)
{
  double const x_distance = left.position.x - right.position.x;
  double const y_distance = left.position.y - right.position.y;
  return std::sqrt(x_distance * x_distance + y_distance * y_distance);
}

void Incubation_Infection::sane_to_infected(Population& population, int ticks)
{
  auto last_sane = population.S.end();
  auto last_infected = population.I.end();
  for (auto it_sane = population.S.begin(); it_sane != last_sane; ++it_sane) {
    for (auto it_infected = population.I.begin(); it_infected != last_infected;
         ++it_infected) {
      if (it_infected->sub_status == Sub_Status::Infective) {
        if (distance(*it_sane, *it_infected) < limiting_distance_) {
          if (probability_distribution_(random_seed_) <
              infection_probability_) {
            it_sane->sub_status = Sub_Status::Incubation;
            it_sane->ticks_of_infection = ticks;
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
}

void Incubation_Infection::infected_to_recovered(Population& population,
                                                 int ticks)
{
  auto last_infected = population.I.end();
  for (auto it_infected = population.I.begin(); it_infected != last_infected;
       ++it_infected) {
    if (it_infected->ticks_of_infection + incubation_time_ == ticks) {
      it_infected->sub_status = Sub_Status::Infective;
    }
    if (probability_distribution_(random_seed_) < recovery_probability_) {
      it_infected->sub_status = Sub_Status::Recovered;
      it_infected->ticks_of_recovery = ticks;
      population.R.push_back(*it_infected);
      std::iter_swap(it_infected, std::prev(last_infected));
      it_infected = std::prev(it_infected);
      population.I.pop_back();
      last_infected = population.I.end();
    }
  }
}