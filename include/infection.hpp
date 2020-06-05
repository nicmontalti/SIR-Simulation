#ifndef INFECTION_HPP
#define INFECTION_HPP

#include <cassert>
#include <random>
#include "SIR_population.hpp"

class G_Infection
{
 public:
  void virtual update(SIR_Population&, int ticks) = 0;
};

class Simple_Infection : public G_Infection
{
  double const limiting_distance_;
  float const infection_probability_;
  float const recovery_probability_;

  std::mt19937 random_seed_;
  std::uniform_real_distribution<float> probability_distribution_;

  void sane_to_infected(SIR_Population& population, int ticks);
  void infected_to_recovered(SIR_Population& population, int ticks);

 public:
  Simple_Infection(double limiting_distance,
                   float infection_probability,
                   float recovery_probability);

  void update(SIR_Population& population, int ticks) override
  {
    infected_to_recovered(population, ticks);
    sane_to_infected(population, ticks);
  }
  double distance(Person const&, Person const&);
};

class Incubation_Infection : public G_Infection
{
  double const limiting_distance_;
  float const infection_probability_;
  float const recovery_probability_;
  int const incubation_time_;

  std::mt19937 random_seed_;
  std::uniform_real_distribution<float> probability_distribution_;

  void sane_to_infected(SIR_Population& population, int ticks);
  void infected_to_recovered(SIR_Population& population, int ticks);

 public:
  Incubation_Infection(double limiting_distance,
                       float infection_probability,
                       float recovery_probability,
                       int incubation_time_);

  void update(SIR_Population& population, int ticks) override
  {
    sane_to_infected(population, ticks);
    infected_to_recovered(population, ticks);
  }
  double distance(Person const&, Person const&);
};

#endif