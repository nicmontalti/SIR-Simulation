#ifndef SIR_SIMPLE_INFECTION_HPP
#define SIR_SIMPLE_INFECTION_HPP

#include <cassert>
#include <random>
#include "infection.hpp"
#include "population.hpp"

class Simple_Infection : public G_Infection
{
  double const limiting_distance_;
  float const infection_probability_;
  float const recovery_probability_;

  std::mt19937 random_seed_;
  std::uniform_real_distribution<float> probability_distribution_;

  void sane_to_infected(Population& population, int ticks);
  void infected_to_recovered(Population& population, int ticks);
  double distance(Person const&, Person const&);

 public:
  Simple_Infection(double limiting_distance,
                   float infection_probability,
                   float recovery_probability);

  void update(Population& population, int ticks) override
  {
    infected_to_recovered(population, ticks);
    sane_to_infected(population, ticks);
  }
};

#endif