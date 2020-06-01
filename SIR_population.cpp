#include "SIR_population.hpp"
#include <algorithm>
#include <cassert>
#include <random>
#include <vector>

class New_Starting_State
{
  Sub_Status sub_status_;
  std::mt19937& random_seed_;
  std::uniform_real_distribution<double>& position_distribution_;

 public:
  New_Starting_State(
      Sub_Status sub_status,
      std::mt19937& random_seed,
      std::uniform_real_distribution<double>& position_distribution)
      : sub_status_{sub_status}
      , random_seed_{random_seed}
      , position_distribution_{position_distribution}
  {
  }
  Person operator()() const
  {
    double const x = position_distribution_(random_seed_);
    double const y = position_distribution_(random_seed_);
    return Person{Position{x, y}, Velocity{0., 0.}, sub_status_};
  }
};

SIR_Population make_sir_population(int size, int S, int I, int R)
{
  assert(size > 0);
  assert(S >= 0);
  assert(I >= 0);
  assert(R >= 0);

  SIR_Population population{People(S), People(I), People(R)};

  std::mt19937 random_seed(std::random_device{}());
  std::uniform_real_distribution<double> position_distribution{
      0., static_cast<double>(size)};

  New_Starting_State new_sane{
      Sub_Status::Sane, random_seed, position_distribution};
  New_Starting_State new_infected{
      Sub_Status::Infective, random_seed, position_distribution};
  New_Starting_State new_recovered{
      Sub_Status::Recovered, random_seed, position_distribution};

  std::generate(population.S.begin(), population.S.end(), new_sane);
  std::generate(population.I.begin(), population.I.end(), new_infected);
  std::generate(population.R.begin(), population.R.end(), new_recovered);

  return population;
}