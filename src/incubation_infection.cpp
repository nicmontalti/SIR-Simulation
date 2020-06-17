#include "incubation_infection.hpp"
#include <algorithm>
#include <cassert>
#include <cmath>
#include <iterator>

Incubation_Infection::Incubation_Infection(double limiting_distance,
                                           float infection_probability,
                                           float mean_recovery_time,
                                           int incubation_time)
    : limiting_distance_{limiting_distance}
    , infection_probability_{infection_probability}
    , mean_recovery_time_{mean_recovery_time}
    , incubation_time_{incubation_time}
    , random_seed_{std::random_device{}()}
    , probability_distribution_{0.F, 1.F}
    , recovery_time_distribution_{mean_recovery_time_, 1.F}
{
  assert(limiting_distance_ > 0);
  assert(infection_probability_ >= 0 && infection_probability_ <= 1);
  assert(mean_recovery_time_ >= 0);
  assert(incubation_time_ >= 0);
}

double Incubation_Infection::distance(Person const& left, Person const& right)
{
  double const x_distance = left.position.x - right.position.x;
  double const y_distance = left.position.y - right.position.y;
  return std::sqrt(x_distance * x_distance + y_distance * y_distance);
}

void Incubation_Infection::infect(Person& person)
{
  person.sub_status = Sub_Status::Incubation;
  person.ticks_of_infection = ticks_;
  person.ticks_of_recovery = ticks_ + recovery_time_distribution_(random_seed_);
}

void Incubation_Infection::sane_to_infected(Population& population)
{
  auto it_sane = population.S.begin();

  int n_infected_to_check = population.I.size();

  auto check_infection = [&](Person const& infected) {
    if (infected.sub_status == Sub_Status::Infective) {
      if (distance(*it_sane, infected) < limiting_distance_) {
        return probability_distribution_(random_seed_) < infection_probability_;
      }
    }
    return false;
  };

  auto last_sane = population.S.end();

  while (it_sane != last_sane) {
    auto first_to_check = population.I.begin();
    auto check_end = next(first_to_check, n_infected_to_check);
    bool has_been_infected =
        std::find_if(first_to_check, check_end, check_infection) != check_end;

    if (has_been_infected) {
      infect(*it_sane);

      population.I.push_back(*it_sane);

      // Fast erase swapping with back and popping
      std::move(std::prev(last_sane), last_sane, it_sane);
      population.S.pop_back();

      // Updating last_sane, it_sane is already at next person
      last_sane = population.S.end();
    } else {
      // Updating it_sane to next person
      std::advance(it_sane, 1);
    }
  }
}

void Incubation_Infection::infected_to_recovered(Population& population)
{
  auto it_infected = population.I.begin();
  auto last_infected = population.I.end();
  while (it_infected != last_infected) {
    if (it_infected->ticks_of_recovery <= ticks_) {
      it_infected->sub_status = Sub_Status::Recovered;

      population.R.push_back(*it_infected);

      // Fast erase swapping with back and popping
      std::move(std::prev(last_infected), last_infected, it_infected);
      population.I.pop_back();

      // Updating last_infected, it_infected is already at next person
      last_infected = population.I.end();
    } else {
      if (it_infected->sub_status == Sub_Status::Incubation &&
          it_infected->ticks_of_infection + incubation_time_ == ticks_) {
        it_infected->sub_status = Sub_Status::Infective;
      }

      // Updating it_infected to next person to check
      std::advance(it_infected, 1);
    }
  }
}
