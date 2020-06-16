#include "population.hpp"
#include <TRandom.h>
#include <algorithm>
#include <cassert>
#include <vector>

Simulation_State::Simulation_State(int i_size, int S, int I, int R)
    : size{i_size}
    , population{Population{People(S), People(I), People(R)}}
    , ticks{0}
{
  assert(size > 0);
  assert(ticks >= 0);

  class New_Person
  {
    int const size_;
    Sub_Status const sub_status_;
    TRandom random_gen_;

   public:
    New_Person(int size, Sub_Status sub_status)
        : size_{size}, sub_status_{sub_status}, random_gen_{}
    {
      random_gen_.SetSeed();
    }
    Person operator()()
    {
      double const x = random_gen_.Uniform(0., size_);
      double const y = random_gen_.Uniform(0., size_);
      return Person{Position{x, y}, Velocity{0., 0.}, sub_status_};
    }
  };

  std::generate(population.S.begin(),
                population.S.end(),
                New_Person(size, Sub_Status::Sane));
  std::generate(population.I.begin(),
                population.I.end(),
                New_Person(size, Sub_Status::Infective));
  std::generate(population.R.begin(),
                population.R.end(),
                New_Person(size, Sub_Status::Recovered));
}