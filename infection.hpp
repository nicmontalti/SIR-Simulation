#ifndef INFECTION_HPP
#define INFECTION_HPP

#include <cassert>
#include <random>
#include "SIR_population.hpp"

class G_Infection
{
 public:
  bool virtual update(SIR_Population&, int const& ticks = 0) = 0;
};

class Simple_Infection : public G_Infection
{
  int const ticks_frequency_;
  double const limiting_distance_;
  float const infection_probability_;
  float const recovery_probability_;

  std::mt19937 random_seed_;
  std::uniform_real_distribution<float> probability_distribution_;

  void sane_to_infected(SIR_Population&);
  void infected_to_recovered(SIR_Population&);

 public:
  Simple_Infection(int const ticks_frequency,
                   double limiting_distance,
                   float infection_probability,
                   float recovery_probability);

  bool update(SIR_Population& population, int const& ticks) override
  {
    assert(ticks >= 0);
    assert(ticks_frequency_ > 0);
    if (ticks % ticks_frequency_ == 0) {
      sane_to_infected(population);
      infected_to_recovered(population);
      return true;
    } else {
      return false;
    }
  }

  double distance(Person const&, Person const&);
};

#endif