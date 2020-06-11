#include "population.hpp"
#include <algorithm>
#include <cassert>
#include <random>
#include <vector>

Population make_population(int size, int S, int I, int R)
{
  class New_Starting_State
  {
    Sub_Status sub_status_;
    std::mt19937 random_gen_;
    std::uniform_real_distribution<double> position_distribution_;

   public:
    New_Starting_State(int size, Sub_Status sub_status)
        : sub_status_{sub_status}
        , random_gen_{std::random_device{}()}
        , position_distribution_{0., static_cast<double>(size)}
    {
    }
    Person operator()()
    {
      double const x = position_distribution_(random_gen_);
      double const y = position_distribution_(random_gen_);
      return Person{Position{x, y}, Velocity{0., 0.}, sub_status_};
    }
  };

  assert(size > 0);
  assert(S >= 0);
  assert(I >= 0);
  assert(R >= 0);

  Population population{People(S), People(I), People(R)};

  std::generate(population.S.begin(),
                population.S.end(),
                New_Starting_State(size, Sub_Status::Sane));
  std::generate(population.I.begin(),
                population.I.end(),
                New_Starting_State(size, Sub_Status::Infective));
  std::generate(population.R.begin(),
                population.R.end(),
                New_Starting_State(size, Sub_Status::Recovered));

  return population;
}