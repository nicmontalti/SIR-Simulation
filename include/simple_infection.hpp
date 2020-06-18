#ifndef SIR_SIMPLE_INFECTION_HPP
#define SIR_SIMPLE_INFECTION_HPP

#include <TRandom.h>
#include <algorithm>
#include <cassert>
#include "infection.hpp"
#include "population.hpp"

class Simple_Infection : public G_Infection
{
  double const limiting_distance_;
  float const infection_probability_;
  float const mean_recovery_ticks_;
  float const sd_recovery_ticks_;

  TRandom random_gen_;

  int ticks_;

  void infect(Person& person);
  void sane_to_infected(Population& population);
  void infected_to_recovered(Population& population);

 public:
  Simple_Infection(double limiting_distance,
                   float infection_probability,
                   float mean_recovery_ticks,
                   float sd_recovery_ticks);

  void update(Population& population, int ticks) override
  {
    ticks_ = ticks;
    if (ticks_ == 0) {
      std::for_each(population.I.begin(),
                    population.I.end(),
                    [this](Person& person) { infect(person); });
    }
    infected_to_recovered(population);
    sane_to_infected(population);
  }
  double distance(Person const&, Person const&);
};

#endif