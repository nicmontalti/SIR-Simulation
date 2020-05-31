#ifndef INFECTION_HPP
#define INFECTION_HPP

#include <cassert>
#include <random>
#include "SIR_population.hpp"

class G_Infection
{
 public:
  void virtual update(SIR_Population&, int const& ticks = 0) = 0;
};

class Simple_Infection : public G_Infection
{
  double const limiting_distance_;
  float const infection_probability_;
  float const recovery_probability_;

  std::mt19937 random_seed_;
  std::uniform_real_distribution<float> probability_distribution_;

  void sane_to_infected(SIR_Population&);
  void infected_to_recovered(SIR_Population&);

 public:
  Simple_Infection(double limiting_distance,
                   float infection_probability,
                   float recovery_probability);

  void update(SIR_Population& population, int const& ticks) override
  {
    sane_to_infected(population);
    infected_to_recovered(population);
  }
  double distance(Person const&, Person const&);
};

#endif